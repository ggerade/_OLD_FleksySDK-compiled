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
  
  FILE* fileHandle;
  size_t filesize;

  FLFile* fl_file = nullptr;
  
  short_lut table;

private:

  static FLTrigramsBin * fl_trigrams_bin;
  static int nPredictors;
  FastBinaryFileHeader hdr;  // version of binary file (>= 100 for fast binary files with an index)
  bool active;
  bool hasInMemoryData = false;
  word_id getNextLongWordID(long endOffset);
  
  bool ensureNonMidSentinel();
  int search(word_id longWordID, long startOffset, long middleOffset, long endOffset, int depth);

  // this returns from table loaded in memory
  void getNextCandidatesNormal(map_probs& result, token_ids previous_tokens, int resultsLimit = 0, probability pThreshold = 0);
 
  // this will read the context file and pull requested data

  void prepareNextCandidatesMemoryless(list_pred& result, token_ids previous_tokens, int resultsLimit = 0, probability pThreshold = 0);
  // fast binary version
  void getNextCandidatesFast(list_pred& candidates, word_id wordID, int resultsLimit = 0, probability pThreshold = 0 );
  void getNextCandidates3Gram(list_pred& candidates, token_ids previous_tokens, int resultsLimit, probability pThreshold );  // bigram/trigram combo
  void read_uni_bin(string uni_bin_file);   // string file-spec version
  void read_uni_bin(FLFile * uni_fl_file);  // FLFile version
  void init(FLFile * infile, bool alsoLoadInMemory);  // used by different signature constructors
public:
  FLSingleLevelTokenPredictor(const string& filename, const string& filehash, bool alsoLoadInMemory);  
  FLSingleLevelTokenPredictor(FLFile * infile, bool alsoLoadInMemory);
  ~FLSingleLevelTokenPredictor();
  
  // checkConsistency: will use both normal and memoryless methods, ensures they are consistent and returns the memoryless results
  //  void getNextCandidatesList(list_pred& result, word_id previousTokenID, int resultsLimit = 0, probability pThreshold = 0);
  void getNextCandidatesList(list_pred& result, token_ids previous_tokens, int resultsLimit = 0, probability pThreshold = 0);

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
  unordered_map<word_id, double> unigram_map;
  list_pred unigram_candidates;  
};

#endif // compile guard
