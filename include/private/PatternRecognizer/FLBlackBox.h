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


#define BLACKBOX_BUCKET_SIZE 0.3
// 30 degrees
#define BLACKBOX_ANGLE_BUCKETS_N 12
#define BLACKBOX_BUCKET_ANGLE_SIZE (2 * M_PI / BLACKBOX_ANGLE_BUCKETS_N)

#if 1
#include <map> //1.22s/37.14MB/77.71MB
typedef std::map<long long, const void*> Mymap; //hashtable[6] 1M @ 0.0138 iPhone5
#else
#include <unordered_map> //1.76s/38.62MB/81.04MB
typedef std::unordered_map<long long, const void*> Mymap; //hashtable[6] 1M @ 0.0202 iPhone5
#endif

//#include <tr1/unordered_map>
//typedef std::tr1::unordered_map<long long, const void*> Mymap;

class FLBlackBox {
  
  
private:
  
  long long maxZ;
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
  
public:
  
  
  FLBlackBox();
  ~FLBlackBox();
  int keyCount();
  int totalValuesCount();
  
  void setValue(long long key, const void* newValue, bool realloced);
  const void* getValue(long long key);

  //these are used when the values of the table are not some mutable structures like NSMutableArray.
  //currenty, for example, we use C style unsigned short arrays.
  void appendItem(long long key, unsigned short item);
  void removeItem(long long key, unsigned short item);
  
  
  Mymap::iterator getIterator();
  Mymap::iterator getIteratorEnd();
  float getLoadFactor();
  
  ///////////////////////////////////
  long long constructKey(VoteParameters params);
};

#endif
