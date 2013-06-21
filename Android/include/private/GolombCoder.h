//
//  GolombCoder.h
//  FleksyX
//
//  Created by Kosta Eleftheriou on 2/12/13.
//  Copyright (c) 2013 Kostas Eleftheriou. All rights reserved.
//

#ifndef __FleksyX__GolombCoder__
#define __FleksyX__GolombCoder__

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

typedef vector<bool> BitVector;
typedef vector<uint16_t> IntVector;

class GolombEncodingResult {
public:
  uint8_t log2M;
  BitVector bits;
  size_t elementsEncoded;
  size_t bytesUsed;
  bool includesCount;
};

class GolombCoder {
  
public:
  
  static size_t bytesUsedByEncoding(const IntVector& data, int M, bool includeCount, BitVector& output);
  
  static bool encodeSingleNumber(uint16_t number, int M, BitVector &bits);
  static uint16_t  decodeSingleNumber(const BitVector& bits, int M);
  
  static bool encode(const IntVector& source, int M, bool includeCount, BitVector &bits, size_t maxBits);
  static IntVector decode(const BitVector& bits, int M, bool includesCount);
  
  // this will search through a few possible values for M and return a tuple
  // with results and some other useful info, see GolombEncodingResult
  static GolombEncodingResult maxEncode(const IntVector& source, bool includeCount, uint8_t minBits = 2, uint8_t maxBits = 15);

  static void printGolombEncodingResult(const GolombEncodingResult& g);
  static void printBitVector(const BitVector& bits);
  static bool vectorOnlyContainsUniqueElemets(const IntVector& data);


  static void runTests();
  
};

#endif /* defined(__FleksyX__GolombCoder__) */
