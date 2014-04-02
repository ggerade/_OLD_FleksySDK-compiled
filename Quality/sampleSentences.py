# quick implementation. Not particularly efficient with space

import argparse, re, codecs, random, time

parser = argparse.ArgumentParser(description='Given a text file, this will randomly sample '
                                 'sentences in the text. Outputs to stdout')
parser.add_argument('input', help='Text file')
parser.add_argument('word_count', type=int, help='Desired word count in document')
parser.add_argument('-l', '--length', type=int, default=3, help = 'Sets the minimum number '
                    'of words in a sentence')
args = parser.parse_args()

random.seed(time.clock())
input = codecs.open(args.input, 'r', "utf-8")
text = ""
for line in input:
    text += line.strip()

sentences = re.split("\.", text)
totalCnt = 0
while (totalCnt < args.word_count and len(sentences) > 0):
    temp = []
    for sent in sentences:
        words = re.split(" ", sent)
        rnd = random.random()
        if (len(words) >= args.length):
            if (rnd <= 0.1):
                totalCnt += len(words)
                print(sent.strip() + ".")
            else:
                temp.append(sent)
            
    sentences = list(temp)
