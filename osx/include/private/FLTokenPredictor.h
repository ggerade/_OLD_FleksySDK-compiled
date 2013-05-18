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

protected:
  
  FLSingleLevelTokenPredictorAsync* fsltp[MAX_WORD_DEPTH];
  
public:
  
  // CONSTRUCTORS
  FLTokenPredictor(FLFilePtr &unigram_fl_file,
                   FLFilePtr &bigram_fl_file,
                   FLFilePtr &trigram_fl_file,
                   bool alsoLoadInMemory); 
    
    // DESTRUCTOR
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

  // wrapper function of the above two step process
  void getNextCandidatesList(list_pred& result, token_ids previousTokenIDs, int resultsLimit = 0, probability pThreshold = 0);
  
  string getDescription();
};

#endif /* defined(__FleksyX__FLTokenPredictor__) */
