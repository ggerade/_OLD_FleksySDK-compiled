//
//  Structures.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 6/25/11.
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "FLPoint.h"
#include <vector>

#include "FLString.h"

typedef struct LPCentroid {
  
  //This takes up a lot of the memory.
  
  float angle;
  FLPoint sincos;
  float distance;
  float logDistance;
  
  //float angularDeviation;
  //float distanceDeviation;
  
} LPCentroid;


typedef struct CalculatorStateStruct {
  
  float sum1;
  float sum2;
  float totalWeights;
  
} CalculatorStateStruct;


typedef struct StandardDeviationResult {
  
  float variance;
  float deviation;
  float mean;
  float totalWeights;
  
  int worstIndex1;
  int worstIndex2;
  float worstValue1;
  float worstValue2;
  
} StandardDeviationResult;


typedef struct VoteParameters {
  
  float basisAngle;
  float basisLength;
  
  //TODO: We could use these to rule out translated values early
  //FLPoint baseMidpoint;
  //FLPoint absolutePoint;
  
  FLPoint point;
  
  signed char bucketShiftX;
  signed char bucketShiftY;
  signed char angleBucketShift;
  signed char scaleBucketShift;
  float votingMultipler;

  float votingPower;
  unsigned char votingIndex;
  
  unsigned char pointIndex;
  unsigned char basisIndex1;
  unsigned char basisIndex2;
  
} VoteParameters;



typedef struct VoteResult {
  
  float processingTime;
  int voteCount;
  int wordLength;
  std::vector<VoteParameters> paramsVector;
  
} VoteResult;

#endif
