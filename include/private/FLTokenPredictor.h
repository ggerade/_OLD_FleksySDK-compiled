//
//  FLTokenPredictor.h
//  FleksyX
//
//  Created by Kosta Eleftheriou on 2/12/13.
//  Copyright (c) 2013 Kostas Eleftheriou. All rights reserved.
//

#ifndef __FleksyX__FLTokenPredictor__
#define __FleksyX__FLTokenPredictor__
// C++ headers
#include <iostream>
// Fleksy headers
#include "FLSingleLevelTokenPredictorAsync.h"

#define USE_UTILITIES 0
#if USE_UTILITIES
#include "FleksyUtilities.h"
#endif

#define USE_RANK_METHOD 0
// no need to normalize if USE_RANK_METHOD
#define NORMALIZE_RESULTS 1
#define WEIGHT_EXPONENT (USE_RANK_METHOD ? 2.0 : 1.0)
//#define WEIGHT_EXPONENT 0.0

#define PRINT_INTERMEDIATE_RESULTS 0

class FLTokenPredictor {
 public:
  static double prepareTime;
  static double peekTime;
  static double getTime;

private:
  
  FLSingleLevelTokenPredictorAsync* fsltp[MAX_WORD_DEPTH];

  static char* wordLetters(word_id tokenID);
  static word_id wordID(const char* letters);
   
#if USE_UTILITIES 
  static FleksyUtilities* static_utils;

  void runContextTestForTokens(token_ids tokens, bool print);
  void runContextTestForToken(word_id tokenID, FLSingleLevelTokenPredictorAsync* ftp, list_pred& preds, bool print);
  void runContextTest2ForToken(word_id tokenID, FLSingleLevelTokenPredictorAsync* ftp, map_probs& probs, int wordLength, int depth, float weight);
  void runContextTest2ForLetters(const char* letters, FLSingleLevelTokenPredictorAsync* ftp, map_probs& result, int wordLength, int depth, float weight);
  void runContextTests();
#endif
  
public:
  
  // filename1 is looking 2 words back, filename2 is looking 1 word back. Empty strings can be used to deactivate the different look back levels
  // FLTokenPredictor(const string& filename1, const string& filename2, const string& filehash1, const string& filehash2, bool alsoLoadInMemory, void* utils = NULL  
  FLTokenPredictor(const string& unigram_file, 
                   const string& bigram_file,
                   const string& trigram_file,
                   const string& unigram_hash, 
                   const string& bigram_hash,
                   const string& trigram_hash,
                   bool alsoLoadInMemory, 
                   void* _utils = NULL);
  
  ~FLTokenPredictor();
  
  // this is guaranteed not to block. Client can send multiple requests and they will all be processed in FIFO order
  void prepareNextCandidatesListAsync(token_ids previousTokenIDs);
  
  // this may block until results for this tokenID are calculated
  void peekNextCandidatesList(list_pred& result, token_ids previousTokenIDs, int resultsLimit = 0, probability pThreshold = 0);
  // NOTE: the last token goes in previousTokenIDs.data[0].  The token before that is moved from previousTokenIDs.data[0] to .data[1]
  //
  // e.g consider processing the text stream: "the dog is black" 
  // step 1   data[0] is "the", data[1] is blank
  // step 2   data[0] is "dog", data[1] is "the"
  // step 3   data[0] is "is", data[1]  is "dog"
  // step 4   data[0] is "black", data[1] is "is"
  //
  // see also token_ids::shift (in FLContextCommon.h)

  // wrapper function of the abvove two step process
  void getNextCandidatesList(list_pred& result, token_ids previousTokenIDs, int resultsLimit = 0, probability pThreshold = 0);
  
  string getDescription();
  
  // testing
  void _simpleTest(const char* word1, const char* word2);
  void simpleTest(const char* word1, const char* word2);
  std::vector<int> getRanksForWord(const char* letters);
};

#endif /* defined(__FleksyX__FLTokenPredictor__) */
