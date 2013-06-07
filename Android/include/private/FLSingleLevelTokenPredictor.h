#ifndef FL_SINGLE_LEVEL_TOKEN_PREDICTOR_H
#define FL_SINGLE_LEVEL_TOKEN_PREDICTOR_H
// C headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
// C++ headers
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <vector>
#include <fstream>
// Fleksy headers
#include <PatternRecognizer/FLFile.h>
#include "FLContextCommon.h"
#include "FLTrigramsBin.h"

class FLSingleLevelTokenPredictor {
private:
  FLFilePtr fl_unigrams_file;
  FLFilePtr fl_bigrams_file;
  FLFilePtr fl_trigrams_file;

  FLTrigramsBin * fl_trigrams_bin = NULL;

  bool active = false;
  
  int _bigramFileVersion = 0;
  size_t _bigramCount = 0;
  const uint32_t *_bigramOffsets = NULL;
  const unsigned char *_bigramPredictions = NULL;
  const unsigned char *_bigramFileContents = NULL;

  void getNextCandidatesFast(list_pred& candidates, word_id wordID, int resultsLimit = 0, probability pThreshold = 0 );

  void getNextCandidates3Gram(list_pred& candidates, token_ids previous_tokens, int resultsLimit, probability pThreshold );  // bigram/trigram combo
  void getBiasedUnigramPredictions(list_pred& result, token_ids previous_tokens);
  
public:
  FLSingleLevelTokenPredictor(FLFilePtr &unigramFile, FLFilePtr &bigramFile, FLFilePtr &trigramFile);
  ~FLSingleLevelTokenPredictor();
  
  // checkConsistency: will use both normal and memoryless methods, ensures they are consistent and returns the memoryless results
  //void getNextCandidatesList(list_pred& result, token_ids previous_tokens, int resultsLimit = 0, probability pThreshold = 0);
  void prepareNextCandidatesMemoryless(list_pred& result, token_ids previous_tokens, int resultsLimit = 0, probability pThreshold = 0);
  
  void setActive(bool b);
  bool isActive();
  
  friend class FleksyContextCommon;
  friend class FLContextTester;  

public:
  unordered_map<word_id, probability> unigram_map;
  list_pred unigram_candidates;
};

#endif // compile guard
