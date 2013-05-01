//
//  FLWord.h
//  PatternRecognizer
//
//  Copyright 2011 Syntellia Inc. All rights reserved.
//


#ifndef FLWORD_H
#define FLWORD_H

#include "PrivateStructures.h"
#include "Structures.h"
#include "FLBlackBox.h"


class FLWord {
  
private:
  
  BBValue uniqueID;
  
  FLString* letters;
  FLString* printLetters;

  float frequency;
//  int groupFrequencyRank;
//  int frequencyRank;
  
  int bytesAllocated;
  
  void initFromPoints(short nPoints, FLPoint* points, BBValue uniqueID);
  void* allocateMemoryForItems(size_t count, size_t itemSize);
  float shapeScore(float angleDeviation, float scalePpcm, bool swapped);
  //void calculateLPCentroidsFromPoints(short nPoints, FLPoint* points);
  int getRawSize();

public:
  short nPoints;

  FLPoint* rawPoints;
  //LPCentroid* LPCentroids;
  
  float votes0and1;
  
  //float* anchorScores;
  
  //for input words only. TODO this takes up memory on dictionary words for no reason
  //float* anchorScoresMin;
  //float* anchorScoresMax;
  
  
//  int bestSwapIndex1;
//  int bestSwapIndex2;
  //float bestSwapValue1;
  //float bestSwapValue2;
  
  
//  float scaleLogDeltaVariance;
//  float scalePpcm;
//  float angleDeviation;

  //float logScalePpcm;
  
  
  float cachedTotalDistance;
  float cachedShapeDistance;
  float cachedTransformationDistance;

//  float scaleMean;
//  float angleMean;
//  float txMean;
 
 
  //float scaleMetaDeviation;
  //float angleMetaDeviation;
  //float scaleSkewness;
  //float angleSkewness;
  //float scaleKurtosis;
  //float angleKurtosis;
  
  
  //float angleHash; 
  
  //float sumLogs;
  //float sumLogs2;
  //float sumNologs;
  
  FLPoint absoluteCentroid;

  float contextFrequency;
  
  ////////////////////

  FLWord(short nPoints, FLPoint* points, BBValue uniqueID);
  FLWord(const FLString* letters, float frequency, const FLString* printLetters, short nPoints, FLPoint* pointsToUse, BBValue uniqueID);
  ~FLWord();
  void swapRawPoints(int i1, int i2);
  float getTotalRunningLength();
  float getTransformationDistance();
  float getTotalDistance();

//- (float) calculateDataForInput1:(FLWord *) inputWord allowSwaps:(BOOL)allowSwaps calculatingAnchor:(BOOL) calculatingAnchor calculators:(Calculators) calculators;
//- (void) calcTotalDistanceWithInput:(FLWord *) inputWord;

  const FLString* getLetters();
  const FLString* getPrintLetters();
  
  void setFrequency(float f);
  float getFrequency();
//  void setGroupFrequencyRank(int rank);
//  int getGroupFrequencyRank();
//  int getFrequencyRank();
//  void setFrequencyRank(int rank);
  
  short getNPoints();
  BBValue getUniqueID();
  int getBytesAllocated();

  static bool compareStringOnly(FLWord* thisWord, FLWord* word);
  static bool compareNonExactVotesPass2(FLWord* thisWord, FLWord* word);
//  static bool compareAngle(FLWord* thisWord, FLWord* word);
//  static bool compareScale(FLWord* thisWord, FLWord* word);
//  static bool compareTx(FLWord* thisWord, FLWord* word);
  static bool compareCachedTotalDistance(FLWord* thisWord, FLWord* word);
  static bool compareShapeDistance(FLWord* thisWord, FLWord* word);
  static bool compareExactVotes(FLWord* thisWord, FLWord* word);
  static bool compareExtraVotes(FLWord* thisWord, FLWord* word);
  static bool compareMinusVotes(FLWord* thisWord, FLWord* word);
  
};

typedef std::vector<FLWord*> FLWordList;


#endif
