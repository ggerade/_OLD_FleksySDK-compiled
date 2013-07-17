//
//  FLWord.h
//  PatternRecognizer
//
//  Copyright 2011 Syntellia Inc. All rights reserved.
//


#ifndef FLWORD_H
#define FLWORD_H

#include <memory>

#include "PrivateStructures.h"
#include "Structures.h"
#include "FLBlackBox.h"
#include "FLKeyboard.h"

class FLWord;
typedef std::shared_ptr<FLWord> FLWordPtr;

class FLWord {
  
private:
  
  BBValue uniqueID;
  

  //float frequency;
//  int groupFrequencyRank;
//  int frequencyRank;
  
  
  void initFromPoints(short nPoints, FLPoint points[], BBValue uniqueID);
  void* allocateMemoryForItems(size_t count, size_t itemSize);
  float shapeScore(float angleDeviation, float scalePpcm, bool swapped);
  //void calculateLPCentroidsFromPoints(short nPoints, FLPoint* points);
  int getRawSize();

  bool pointsFromLetters = false;
  short nPoints;
  FLPoint* rawPoints = NULL;
  FLKeyboardPtr keyboard;

public:

  FLStringPtr lettersPtr;
  FLStringPtr printLettersPtr;

  FLPoint getPoint(size_t pointIdx) const;
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
  

  float contextFrequency;
  
  bool canBeRemovedByUser;
  
  ////////////////////

  FLWord(short nPoints, FLPoint* points, BBValue uniqueID);
  FLWord(FLStringPtr &_letters, FLStringPtr &_printLetters, short _nPoints, FLPoint pointsToUse[], bool usePointsFromLetters, BBValue _uniqueID, bool canBeRemoved, FLKeyboardPtr &keyboardPtr);
  ~FLWord();
  float getTotalRunningLength();
  float getTransformationDistance();
  float getTotalDistance();

//- (float) calculateDataForInput1:(FLWord *) inputWord allowSwaps:(BOOL)allowSwaps calculatingAnchor:(BOOL) calculatingAnchor calculators:(Calculators) calculators;
//- (void) calcTotalDistanceWithInput:(FLWord *) inputWord;

  FLStringPtr getLetters();
  FLStringPtr getPrintLetters();
  
//  void setFrequency(float f);
//  float getFrequency();
//  void setGroupFrequencyRank(int rank);
//  int getGroupFrequencyRank();
//  int getFrequencyRank();
//  void setFrequencyRank(int rank);
  
  short getNPoints() const;
  BBValue getUniqueID();
  int getBytesAllocated();

  static bool compareStringOnly(FLWord* thisWord, FLWord* word);
//  static bool compareAngle(FLWord* thisWord, FLWord* word);
//  static bool compareScale(FLWord* thisWord, FLWord* word);
//  static bool compareTx(FLWord* thisWord, FLWord* word);
  static bool compareShapeDistance(FLWord* thisWord, FLWord* word);
  static bool compareExactVotes(FLWord* thisWord, FLWord* word);
  static bool compareExtraVotes(FLWord* thisWord, FLWord* word);
  static bool compareMinusVotes(FLWord* thisWord, FLWord* word);
  
};

typedef std::vector<FLWord*> FLWordList;
typedef std::vector<FLWordPtr> FLWordPtrList;


#endif
