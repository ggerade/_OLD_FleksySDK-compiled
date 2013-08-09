//
//  FLShapeTrie.h
//  FleksySDK
//
//  Created by Kosta Eleftheriou on 7/25/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLShapeTrie__
#define __FleksySDK__FLShapeTrie__

// ~10% speedup
#define FLSHAPETRIE_FLATTEN_FOR_INLINE_OPTIMIZATION 0

#include <iostream>
#include "FLTrie.h"
#include "FLKeyboard.h"

// The length/depth beyond which we will only keep and use half the shape data.
// Theoretically lossy, practically lossless for values >= 8. Set to >= FLEKSY_MAX_WORD_SIZE to disable
#define OPTIMIZE_BEYOND_LENGTH 99998

using namespace std;

class FLShapeEngineResultEntry {
private:
  FLString* str;
  float totalScore;
public:
  FLShapeEngineResultEntry(const FLChar* chars, size_t length, float totalScore) { assert(chars != NULL); assert(length > 0); assert(length < 20); this->str = new FLString(chars, length); this->totalScore = totalScore; }
  ~FLShapeEngineResultEntry() { delete str; } ;
  FLString* getStr() { assert(str != NULL); return str; }
  float getTotalScore() { return totalScore; }
};

typedef METADATA_TYPE BasisData[FLEKSY_MAX_WORD_SIZE][FLEKSY_MAX_WORD_SIZE];

class FLShapeTrie : public FLTrie {
  
private:
  
  float precomputedDistances[256][256];
  float absoluteValues[256][256];
  FLPoint cachedPoints[256];
  
  FLPoint* tapPoints;
  size_t inputWordNPoints;
  
  size_t resultsMaxSize;
  BasisData inputWordBasisData;
  list<FLShapeEngineResultEntry*> results;
  
  FLPoint getPointOfWord(const FLString& word, int i);
  FLPoint getPointOfInputWord(int i);
  static FLPoint getBasisCoordsForWord(FLPoint point, FLPoint b1, FLPoint b2, bool convertToBucket, bool cap);
  static uint8_t getCompactBasisCoordsForWord(FLPoint point, FLPoint b1, FLPoint b2, bool cap);
  
  static uint8_t _getBasisCoordsForWord(FLPoint bp1, FLPoint bp2, FLPoint p, FLPoint* result, bool cap);
  uint8_t getBasisCoordsForInputWord(int bi1, int bi2, int pi, FLPoint* result, bool cap);
  uint8_t getBasisCoordsForWord(const FLString& word, int bi1, int bi2, int pi, FLPoint* result, bool cap);
  
  float getScore(FLTrieNode* child, ssize_t loopLimit, METADATA_TYPE* inputData);

  void generateInputWordBasisData();
  static void precomputeBasisDataFunction(TrieStack& stack, void* obj);
  void precomputeBasisData(FLTrieNode* node, FLString& word);
  void precomputeBasisData();
  void getMatches(FLTrieNode* node, FLChar* word2, float totalScore, uint8_t depth);
  
  
public:
  FLKeyboard* keyboard;
  FLShapeTrie(FLKeyboard* keyboard);
  void postLoad();
  double getMatches(FLPoint tapPoints[], size_t tapCount, vector<FLShapeEngineResultEntry*>& results, bool print = false);
};

#if FLSHAPETRIE_FLATTEN_FOR_INLINE_OPTIMIZATION
#include "FLShapeTrie.cpp"
#endif

#endif /* defined(__FleksySDK__FLShapeTrie__) */
