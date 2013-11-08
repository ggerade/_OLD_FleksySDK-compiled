//
//  FLSpaceHelper.h
//  FleksySDK
//
//  Created by Kosta Eleftheriou on 6/25/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLSpaceHelper__
#define __FleksySDK__FLSpaceHelper__

#if 0

#include <iostream>
#include <map>
#include <vector>
#include <pthread.h>
#include "FLPoint.h"
#include "FLFile.h"
#include "FLWord.h"

// This needs to be removed when FLContext* refactoring is done...
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */

typedef int word_id;
typedef std::unordered_map<word_id, probability> map_probs;

#define MAX_WORD_DEPTH (2)  // was 2 (jfm)
#define FL_NO_TOKEN       0
#define FL_UNKNOWN_TOKEN -1
#define FL_ANY_TOKEN     -2
#define FL_STOP_SIGNAL   -3

#define IS_TOKEN_VALID_FOR_SEARCH(_token_id_) ( \
_token_id_ != FL_NO_TOKEN && \
_token_id_ != FL_UNKNOWN_TOKEN && \
_token_id_ != FL_ANY_TOKEN && \
_token_id_ != FL_STOP_SIGNAL && \
_token_id_ < FL_MAX_WORD_ID \
)

class token_ids {
public:
  word_id data[MAX_WORD_DEPTH];
  
  void reset(word_id defaultValue = FL_NO_TOKEN) { for(int i = 0; i < MAX_WORD_DEPTH; i++) { data[i] = defaultValue; } }
  
  token_ids(word_id n = FL_NO_TOKEN) { reset(n); }
  
  bool isEqualToTokens(const token_ids& t) {
    for(int i = 0; i < MAX_WORD_DEPTH; i++) { if(data[i] != t.data[i]) return false; }
    return true;
  }
  
  bool isStopSignal() { return isEqualToTokens(token_ids(FL_STOP_SIGNAL)); }
  
  int activeTokens() {
    int result = 0;
    // Note: we are searching backwards, and will return as soon as we hit the first non-valid/non-active token
    for(int i = 0; i < MAX_WORD_DEPTH; i++) {
      if(!IS_TOKEN_VALID_FOR_SEARCH(data[i])) { return result; }
      else { result++; }
    }
    return result;
  }
  
  void print() { for(int i = 0; i < MAX_WORD_DEPTH; i++) { LOGI("tokens_id.data[%d] %d\n", i, data[i]); } }
  
  const char * c_str() {
    char tmpBuffer[MAX_WORD_DEPTH * 80];
    size_t atTmpBuffer = 0;
    for(int i = 0; i < MAX_WORD_DEPTH; i++) { atTmpBuffer += snprintf(tmpBuffer + atTmpBuffer, sizeof(tmpBuffer) - atTmpBuffer, "tokens_id.data[%d] %d\n", i, data[i]); }
    std::string result = std::string(tmpBuffer);
    return result.c_str();
  }
};

static token_ids STOP_SIGNAL = token_ids(FL_STOP_SIGNAL);

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

class FLTokenPredictor;

typedef std::map<word_id, map_probs> IdMapProbs;
typedef std::map<size_t, IdMapProbs> IndexIdMapProbs;

class FLSpaceHelper {
  
  static float minX;
  static float maxX;
  static float minY;
  
  token_ids lastPreparedTokenIDs;
  void* systemsIntegrator;
  FLTokenPredictor* ftp;
  std::vector<FLPoint> _points;
  
  IndexIdMapProbs data;
  
  bool producer_thread_created = false;
  bool producer_thread_joined = false;
  volatile bool _producerThreadShouldStop = false; // Protected by request_mutex
  pthread_t producer_thread; // background thread to perform the heavy task in producerThread()
  
  pthread_mutex_t request_mutex    = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t processing_mutex = PTHREAD_MUTEX_INITIALIZER;
  
  pthread_cond_t request_available = PTHREAD_COND_INITIALIZER;
  //pthread_cond_t data_available    = PTHREAD_COND_INITIALIZER;
  
  
  void getNextRequest(std::vector<FLPoint>& result); // for producer to fetch next request or block until there is one
  static void* producerThread(void* arg); //wrapper for instance method
  void producerThread(); // where the processing is done
  
  
public:
  FLSpaceHelper(FLFilePtr &file1, FLFilePtr &file2, FLFilePtr &file3, void* systemsIntegrator);
  ~FLSpaceHelper();
  
  void stopBackgroundThread();
  
  void pushTap(FLPoint tap);
  bool popTap();
  void clearTaps();

  void getResults(IndexIdMapProbs& results);
  void printData(IndexIdMapProbs& results);
  
  void setLastPreparedContextResults(token_ids tokenIDs);
  static bool tapMayBeSpace(FLPoint tap);
};

#endif

#endif /* defined(__FleksySDK__FLSpaceHelper__) */
