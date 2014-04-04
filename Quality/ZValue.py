#!/usr/bin/python3

import sys
import FileIO
import codecs
import re

file = codecs.open(sys.argv[1], "r", "utf-8")
totalSum = 0
totalErr = 0
values = []
for line in file:
    words = FileIO.breakLine(line, 0)
    try:
        cnt = float(words.pop())
        rate = float(words.pop())
        
        if (rate < 0.9):
            totalSum += cnt
            totalErr += rate*cnt

    except ValueError:
        pass

print(totalErr/totalSum, totalErr, totalSum)
