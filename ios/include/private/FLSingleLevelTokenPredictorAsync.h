#ifndef FL_SINGLE_LEVEL_TOKEN_PREDICTOR_ASYNC_H
#define FL_SINGLE_LEVEL_TOKEN_PREDICTOR_ASYNC_H
// Fleksy headers
#include "FLSingleLevelTokenPredictor.h"
// C++ headers
#include <iostream>
#include <queue>
// POSIX headers
#include <pthread.h>

#define MAXIMUM_REQUESTS_BEFORE_BLOCKING 2

class FLSingleLevelTokenPredictorAsync : public FLSingleLevelTokenPredictor {
public:
  static double peekWait;
  static double peekLoopTime;
  static double totalPeek;
private:
  unsigned int counter = 0;  // for debug trace

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
  
  
  bool producer_thread_created = false;
  pthread_t producer_thread; // background thread to perform the heavy task in producerThread()
  queue<token_ids> requestedTokenIDs; // FIFO requests  -- convert to queue<token_ids> requestedTokenIDs
  token_ids lastProcessedTokenIDs; // marked by producer for consumer to ensure desired results  -- convert to lastProcessedTokenIDs
  list_pred lastResults;
  
  void log(const char* format, ...);
  
  void getNextRequest(token_ids& result); // for producer to fetch next request or block until there is one
  static void* producerThread(void* arg); //wrapper for instance method
  void producerThread(); // where the processing is done
  size_t numberOfPendingRequests();

public:
  FLSingleLevelTokenPredictorAsync(FLFilePtr &uni_file, FLFilePtr &infile, FLFilePtr &tri_file);
  ~FLSingleLevelTokenPredictorAsync();
  
  // this is guaranteed not to block unless we already have more than MAXIMUM_REQUESTS_BEFORE_BLOCKING requests.
  // Client can send multiple requests and they will all be processed in FIFO order
  void prepareNextCandidatesListAsync(token_ids previousTokenIDs);
  
  // this may block until results for this tokenID are calculated
  bool peekNextCandidatesList(list_pred& result, token_ids previousTokenIDs, int resultsLimit = 0, probability pThreshold = 0);
};


#endif // compile guard
