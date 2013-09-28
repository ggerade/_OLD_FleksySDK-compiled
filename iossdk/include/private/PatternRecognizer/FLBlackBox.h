//
//  FLBlackBox.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 7/9/11.
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#ifndef FLBLACKBOX_H
#define FLBLACKBOX_H

#include "Structures.h"
#include <math.h>


#define BLACKBOX_BUCKET_SIZE 0.3f

// 30 degrees
#define BLACKBOX_ANGLE_BUCKETS_N 12
#define BLACKBOX_BUCKET_ANGLE_SIZE (2.0f * (float)M_PI / (float)BLACKBOX_ANGLE_BUCKETS_N)

// This uses the absolute angle of the basis. See VoteParameters.basisAngle
#define BLACKBOX_USE_ANGLE 1

//these need to fit in 5 bits for now, so <= 31, and not conflict with ACTUAL base IDs that might be that large! TODO
#define BASEPOINT_CUSTOM1_ID 29
#define BASEPOINT_CUSTOM2_ID (BASEPOINT_CUSTOM1_ID + 1)


typedef uint32_t BBKey;
typedef uint16_t BBValue;

#if 1
#include <map> //1.22s/37.14MB/77.71MB
typedef std::map<BBKey, const BBValue*> Mymap; //hashtable[6] 1M @ 0.0138 iPhone5
#else
#include <unordered_map> //1.76s/38.62MB/81.04MB
typedef std::unordered_map<BBKey, const BBValue*> Mymap; //hashtable[6] 1M @ 0.0202 iPhone5
#endif

//#include <tr1/unordered_map>
//typedef std::tr1::unordered_map<BBKey, const BBValue*> Mymap;


class FLBlackBox {
  
  
private:
  
  BBKey maxZ;
  
  int maxX;
  int maxY;
  int minX;
  int minY;
  //int maxValues;
  //int minValues;
  long requests;
  
  //perform tests to ensure >32-bit keys are ok, more tests to come (eg. performance)
  void testOperation();
  Mymap hashtable;
  Mymap mallocedHashtable;
  
  bool isValueMalloced(BBKey key);

public:
  
  int tag;
  
  FLBlackBox(int tag);
  ~FLBlackBox();
  size_t keyCount();
  size_t totalValuesCount();
  
  void setValue(BBKey key, const BBValue* newValue, bool freeWhenDone);
  const void* getValue(BBKey key);

  void appendItem(BBKey key, BBValue item);
  void removeItem(BBKey key, BBValue item);
  
  
  Mymap::iterator getIterator();
  Mymap::iterator getIteratorEnd();
  float getLoadFactor();
  
  ///////////////////////////////////
  BBKey constructKey(VoteParameters params);
};

#endif
