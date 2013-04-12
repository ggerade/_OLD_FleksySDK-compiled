//
//  FLSocketsCommon.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 20/11/2011.
//  Copyright (c) 2011 Syntellia Inc. All rights reserved.
//

//TODO THIS IS NOT ONLY FOR IPC, RENAME TO EG "FLRequestReposnse.h"
//FleksyClient_NOIPC should not be importing something called XXXsocketsXXX

#ifndef FLSOCKETSCOMMON_H_
#define FLSOCKETSCOMMON_H_

#include <PatternRecognizer/FLPoint.h>
#include <PatternRecognizer/Structures.h>

#define MAX_TOKEN_LENGTH 50

//http://stackoverflow.com/questions/2060974/dynamic-array-in-struct-c
class FLRequest {
public:
  FLChar previousToken1[MAX_TOKEN_LENGTH];
  FLChar previousToken2[MAX_TOKEN_LENGTH];
  FLChar platformSuggestions[1024];
  bool debug;
  double requestTime;
  int pointsN;
  FLPoint points[];
  //////////////////////////////////////////
  //~FLRequest();
  static FLRequest* FLRequestMake(int pointsN, const FLString* previousToken1, const FLString* previousToken2, bool debug = false);
  void setPlatformSuggestions(FLString* s);
  int getSize();
};

class FLResponseEntry {
public:
  float stringEditDistance;
  float euclideanDistance;
  float shapeScore;
  float overallScore;
  //float frequency;
  //int frequencyRank;
  //int groupFrequencyRank;
  float contextFrequency;
  bool platform;
  bool fleksy;
  int pointsN;
  int lettersN;
  //rather than a FLString or FLString*, so that contents are inline
  FLChar letters[];
  //////////////////////////////////////////
  static FLResponseEntry* FLResponseEntryMake(const FLString* letters);
  int getSize();
};

typedef std::vector<FLResponseEntry*> FLResponseEntryVector;

class FLResponse {
public:
  double processingTimeApple;
  double processingTimeFleksyPass1;
  double processingTimeFleksyPass2;
  double totalServerTime;
  double clientRequestTime;
  double serverReceivedTime;
  double serverReplyTime;
  int candidatesN;
  FLResponseEntry candidates[];
  //////////////////////////////////////////
  // this will copy and then free contents of FLResponseEntries in entries
  static FLResponse* FLResponseMake(FLResponseEntryVector& entries);
  //~FLResponse();
  FLResponseEntry* getCandidate(int n);
  int getSize();
};

#endif
