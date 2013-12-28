#!/usr/bin/python3
"""
Runs accurate simulate taps on a given file with failrates from a matching context file. Expects failure 
rate file to have format:

RANK failrate

Results are dumped to stdout

RANK RANK_MOST_FAILED PHRASE {Suggestion Count} True/False 

Given phrase {A B C} with most common suggestion being D in place of C
RANK: rank of phrase in ngram data
RANK_MOST_FAILED: rank of phrase {A B D}
{}: suggestion list
True/False: is whether or not the reversed phrase passed the simulation. For example the 
phrase {A B D} is typed with the expectation thatD will be changed to C

arg1 - failure rate file
arg2 - context file associated with failure rate
arg3 - language-country 
arg4 - failure threshold
arg5 - number of cycles to run
"""

import sys, codecs, os, operator
import subprocess

user = os.getenv("USER")
exec = "/Users/" + user + "/Library/Developer/Xcode/DerivedData/FleksySDK-ddtdrokihvkvteeirffxtjnqxvhs/Build/Products/Release/SimAccurateTaps"


def readContext(filename):
    contextFile = codecs.open(filename, 'r', 'utf-8')
    phraseList  = []
    phraseFreqMap = {}
    rank = 0
    for phrases in contextFile:
        words = phrases.lower().split(' ')
        words.pop(len(words)-1)
        phraseList.append(words)

        if (len(words) > 1):
            subphrase = " ".join(words[0:len(words)-2])
            targ = words[len(words)-1]
            if (subphrase in phraseFreqMap):
                phraseFreqMap[subphrase][targ] = rank
            else:
                temp = {}
                temp[targ] = rank
                phraseFreqMap[subphrase] = temp

        rank += 1

    return phraseList, phraseFreqMap

def parseFailFileLine(line):
    line = line.strip('\n ')
    words = line.split(' ')
    failrate = 0
    index = -1
    if (len(words) == 2):
        try:
            failrate = float(words[1])
            index = int(words[0])
        except ValueError:
            print("error:", line)

    return failrate, index

def launchProc(jetLoc, cycles, phrase):
    p1 = subprocess.Popen([exec, jetLoc, str(cycles)] + phrase, stdout = subprocess.PIPE)
    p2 = subprocess.Popen(["tail", "-n 2"], stdin = p1.stdout, stdout = subprocess.PIPE)
    p1.stdout.close()
    return p2.communicate()[0].decode(encoding='utf-8').strip().split('\n')

def failedWordFreq(line):
    failedFreq = {}
    # alternates between word and count
    words = line.split(' ')
    for i in range(0, len(words)-1, 2):
        failedFreq[words[i]] = int(words[i+1])

    return failedFreq

def checkForFalseNegFailure(output, threshold):
    maxFailed = ""
    failed = len(output) == 2 and float(output[1]) >= threshold
    if (failed):
        failedFreq = failedWordFreq(output[0])
        maxFailed = max(failedFreq.items(), key=operator.itemgetter(1))[0]

    return maxFailed, failed

def checkIfReversedSucceeded(output, threshold):
    success = True
    if (len(output) == 2 and float(output[1]) < threshold):
        failedFreq = failedWordFreq(output[0])
        if (targ in failedFreq):
            cnt = float(failedFreq[targ])
            success = cnt/float(cycles) > threshold

    return success
                
if (len(sys.argv) < 6):
    exit()

phraseList, phraseFreqMap = readContext(sys.argv[2])
failFile = codecs.open(sys.argv[1], 'r', 'utf-8')
lang = sys.argv[3]
threshold = float(sys.argv[4])
cycles = int(sys.argv[5])
jetLoc = "../Android/FleksySDKResources/encrypted/resourceArchive-" + lang + ".jet"
                      
fnegOrig = 0
fnegCur = 0
reversed = 0
for line in failFile:
    failrate, index = parseFailFileLine(line)
    if (failrate >= threshold and index >= 0):
        maxFailed = ""
        fnegOrig += 1
        phrase = phraseList[index]
        output = launchProc(jetLoc, cycles, phrase)
        maxFailed, failed = checkForFalseNegFailure(output, threshold)

        if (failed):
            fnegCur += 1
            targ = phrase.pop(len(phrase)-1)
            phrase.append(maxFailed)          
            outputRev = launchProc(jetLoc, cycles, phrase)
            successRev = checkIfReversedSucceeded(outputRev, threshold)
            if (successRev):
                reversed += 1

            phrase[len(phrase)-1] = targ
            freqDict = phraseFreqMap[" ".join(phrase[0:len(phrase)-2])]
            suggCnt = "NA"
            if (maxFailed in freqDict):
                suggCnt = freqDict[maxFailed]
            print(index, suggCnt, "_".join(phrase), output[0], successRev);

print("False negative:", fnegOrig, float(fnegOrig-fnegCur)/float(fnegOrig))

revRate = 1.
if (fnegCur > 0):
    revRate = float(reversed)/float(fnegCur)
print("Reversed:", reversed, revRate);
