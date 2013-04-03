#ifndef FL_SINGLE_LEVEL_TOKEN_PREDICTOR_ASYNC_H
#define FL_SINGLE_LEVEL_TOKEN_PREDICTOR_ASYNC_H
// Fleksy headers
#include "FLSingleLevelTokenPredictor.h"
// C++ headers
#include <iostream>
#include <queue>
// POSIC headers
#include <pthread.h>

class FLSingleLevelTokenPredictorAsync : public FLSingleLevelTokenPredictor {
 public:
  static double peekWait;
  static double peekLoopTime;
  static double totalPeek;
private:
  unsigned int counter = 0;  // for debug trace

  token_ids previous_tokens;
  // MUTEXES
  // simple print mutex
  pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
  // to guard between prepareNextCandidatesListAsync (consumer) and getNextRequest (producer)
  pthread_mutex_t request_mutex = PTHREAD_MUTEX_INITIALIZER;
  // to guard between peekNextCandidatesList (consumer) and producerThread (producer)
  pthread_mutex_t processing_mutex = PTHREAD_MUTEX_INITIALIZER;
  
  // CONDITIONS
  // signals to producer that a request is available
  pthread_cond_t request_available = PTHREAD_COND_INITIALIZER;
  // signals to consumer that results are ready
  pthread_cond_t data_available = PTHREAD_COND_INITIALIZER;
  
  
  
  pthread_t producer_thread; // background thread to perform the heavy task in producerThread()
  queue<word_id> requestedTokenIDs; // FIFO requests
  word_id lastProcessedTokenID = 0; // marked by producer for consumer to ensure desired results
  list_pred lastResults;
  
  void log(const char* format, ...);
  
  void getNextRequest(word_id& result); // for producer to fetch next request or block until there is one
  static void* producerThread(void* arg); //wrapper for instance method
  void producerThread(); // where the processing is done

public:
  FLSingleLevelTokenPredictorAsync(const string& filename, const string& filehash, bool alsoLoadInMemory);
  ~FLSingleLevelTokenPredictorAsync();
  
  // this is guaranteed not to block. Client can send multiple requests and they will all be processed in FIFO order
  void prepareNextCandidatesListAsync(word_id previousTokenID);
  
  // this may block until results for this tokenID are calculated
  void peekNextCandidatesList(list_pred& result, word_id previousTokenID, int resultsLimit = 0, probability pThreshold = 0);
};


#endif // compile guard
