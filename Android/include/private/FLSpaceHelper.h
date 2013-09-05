//
//  FLSpaceHelper.h
//  FleksySDK
//
//  Created by Kosta Eleftheriou on 6/25/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLSpaceHelper__
#define __FleksySDK__FLSpaceHelper__

#include <iostream>
#include "FLTokenPredictor.h"
#include <pthread.h>

typedef map<word_id, map_probs> IdMapProbs;
typedef map<size_t, IdMapProbs> IndexIdMapProbs;

class FLSpaceHelper {
  
  static float minX;
  static float maxX;
  static float minY;
  
  token_ids lastPreparedTokenIDs;
  void* systemsIntegrator;
  FLTokenPredictor* ftp;
  vector<FLPoint> _points;
  
  IndexIdMapProbs data;
  
  bool producer_thread_created = false;
  pthread_t producer_thread; // background thread to perform the heavy task in producerThread()
  
  pthread_mutex_t request_mutex    = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t processing_mutex = PTHREAD_MUTEX_INITIALIZER;
  
  pthread_cond_t request_available = PTHREAD_COND_INITIALIZER;
  //pthread_cond_t data_available    = PTHREAD_COND_INITIALIZER;
  
  
  void getNextRequest(vector<FLPoint>& result); // for producer to fetch next request or block until there is one
  static void* producerThread(void* arg); //wrapper for instance method
  void producerThread(); // where the processing is done
  
  
public:
  FLSpaceHelper(FLFilePtr &file1, FLFilePtr &file2, FLFilePtr &file3, void* systemsIntegrator);
  ~FLSpaceHelper();
  
  void pushTap(FLPoint tap);
  bool popTap();
  void clearTaps();

  void getResults(IndexIdMapProbs& results);
  void printData(IndexIdMapProbs& results);
  
  void setLastPreparedContextResults(token_ids tokenIDs);
  static bool tapMayBeSpace(FLPoint tap);
};


#endif /* defined(__FleksySDK__FLSpaceHelper__) */
