import argparse, re, codecs, random, time

parser = argparse.ArgumentParser(description='Given a text file, this will randomly sample '
                                 'sentences in the text. Outputs to stdout')
parser.add_argument('input', help='Text file')
parser.add_argument('threshold', type=float, help='Cutoff level, ie 0.1 means 10% of the sentences '
                    'will be kept')
parser.add_argument('-l', '--length', type=int, default=3, help = 'Sets the minimum number '
                    'of words in a sentence')
parser.add_argument('-w', '--word_count', type=int, default=3, help='Desired word count '
                    'in document')
args = parser.parse_args()

random.seed(time.clock())
input = codecs.open(args.input, 'r', "utf-8")
text = ""
for line in input:
    text += line.strip()

sentences = re.split("\.", text)
totalCnt = 0
for sent in sentences:
    words = re.split(" ", sent)
    rnd = random.random()
    if (len(words) >= args.length and rnd <= args.threshold):
        totalCnt += len(words)
        print(sent.strip() + ". ")

    if (totalCnt >= args.word_count):
        break;




