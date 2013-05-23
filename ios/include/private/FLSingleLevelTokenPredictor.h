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

  string _filename;
  string _filehash;
  
  size_t filesize;

  FLFilePtr fl_unigrams_file;
  FLFilePtr fl_bigrams_file;
  FLFilePtr fl_trigrams_file;
  
  short_lut table;

private:

  FLTrigramsBin * fl_trigrams_bin;
  static int nPredictors;
  FastBinaryFileHeader hdr;  // version of binary file (>= 100 for fast binary files with an index)
  bool active;
  bool hasInMemoryData = false;
  
  void fileSanityChecks();
  
  // this returns from table loaded in memory
  void getNextCandidatesNormal(map_probs& result, token_ids previous_tokens, int resultsLimit = 0, probability pThreshold = 0);
 
  // fast binary version
  void getNextCandidatesFast(list_pred& candidates, word_id wordID, int resultsLimit = 0, probability pThreshold = 0 );
  void getNextCandidates3Gram(list_pred& candidates, token_ids previous_tokens, int resultsLimit, probability pThreshold );  // bigram/trigram combo
  void read_uni_bin(FLFilePtr &uni_fl_file);  // FLFile version
  void init(FLFilePtr &uni_file, FLFilePtr &infile, FLFilePtr &tri_file, bool alsoLoadInMemory);  // used by different signature constructors
  void getBiasedUnigramPredictions(list_pred& result, token_ids previous_tokens);
  
public:
  FLSingleLevelTokenPredictor(FLFilePtr &uni_file, FLFilePtr &infile, FLFilePtr &tri_file, bool alsoLoadInMemory);
  ~FLSingleLevelTokenPredictor();
  
  // checkConsistency: will use both normal and memoryless methods, ensures they are consistent and returns the memoryless results
  //void getNextCandidatesList(list_pred& result, token_ids previous_tokens, int resultsLimit = 0, probability pThreshold = 0);
  void prepareNextCandidatesMemoryless(list_pred& result, token_ids previous_tokens, int resultsLimit = 0, probability pThreshold = 0);
  
  void setActive(bool b);
  bool isActive();
  
  string& getFilename();
  string getFileHash();

  static int get_num_pred () { return nPredictors; };

  static double totalFast;

  friend class FleksyContextCommon;
  friend class FLContextTester;  

public:
  // n-gram combination members (jfm)
  //unordered_map<word_id, probability> unigram_map;  // Kostas workaround
  unordered_map<word_id, double> unigram_map;         // old way
  list_pred unigram_candidates;  
};

#endif // compile guard
