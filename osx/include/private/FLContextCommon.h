//
//  FleksyContextCommon.h
//  FleksyContext
//
//  Created by Kostas Eleftheriou on 1/4/13.
//  Copyright (c) 2013 Syntellia Inc. All rights reserved.
//

// identifiers with two adjacent underscores are reserved in C++ standard
//  http://stackoverflow.com/questions/228783/what-are-the-rules-about-using-an-underscore-in-a-c-identifier

#ifndef FleksyContext_FleksyContextCommon_h
#define FleksyContext_FleksyContextCommon_h

#include <sys/syslimits.h>

// standard C++ headers
#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <list>
// ANSI C Headers for C++
#include <cassert>
#include <stdexcept>

// Fleksy headers
#include <PatternRecognizer/CoreSettings.h>
#include <PatternRecognizer/Platform.h>
#include <PatternRecognizer/FLFile.h>

#include "TimeFunctions.h"
#include "GolombCoder.h"

#define MAX_WORD_DEPTH (2)  // was 2 (jfm)

// max count of trace messages reported by functions
// once function has been called FL_MAX_COUNT times, it goes silent
const unsigned int FL_MAX_COUNT = 5;  // default to zero (set to non-zero such as 5 for trace debuggin)
const unsigned int FL_COCA_SIZE = 420170105;  // think this is the number of words in the Mark Davies COCA corpus (our training set)  -- jfm
const unsigned int FL_TRIGRAM_SIGNIFICANT_COUNT = 1;  // used in combinePreds to decide what to do if both bigrams and trigrams make a prediction


const unsigned int FL_SIGNIFICANT_COUNT = 100; // was 20; // used to determine whether the absence of a trigram or bigram gives statistically signficant information on the probability of the bigram or trigram.  If unigram frequency predicts a count above this value, then lack of unigram/bigram gives information -- use 0 prob estimate in this case.
const unsigned int FL_MAX_CANDIDATES = 9991000;  // maximum number of candidates returned (for unigrams right now)
const float        FL_UNI_SCALE = 0.1f;  // max range for unigram probability (bit larger than probability of "the")
const unsigned int FL_READ_REPORT = 20000;  // report read info every FL_READ_REPORT reads (when FL_FLEKSY_TRACE set)

using namespace std;

typedef int word_id;
typedef float probability;
typedef unordered_map<word_id, probability> map_probs;
typedef struct short_lut { map_probs data[FL_MAX_WORD_ID]; } short_lut;

#define FL_NO_TOKEN       0
#define FL_UNKNOWN_TOKEN -1
#define FL_ANY_TOKEN     -2
#define FL_STOP_SIGNAL   -3

#define USE_IDS_PACKING 1
#define USE_PROBS_PACKING 1

#define PROBS_PACKED_RLE  1 << 29
#define PROBS_PACKED  1 << 30
#define IDS_PACKED    1 << 31

#define FLAG_BITS (PROBS_PACKED_RLE | PROBS_PACKED | IDS_PACKED)
#define OFFSET_BITS ((1 << 29) - 1)


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
      if((data[i] == FL_NO_TOKEN) || (data[i] == FL_STOP_SIGNAL)) { return result; }
      else { result++; }
    }
    return result;
  }

  void print() { for(int i = 0; i < MAX_WORD_DEPTH; i++) { LOGI("tokens_id.data[%d] %d\n", i, data[i]); } }

  const char * c_str() {
    char tmpBuffer[MAX_WORD_DEPTH * 80];
    size_t atTmpBuffer = 0;
    for(int i = 0; i < MAX_WORD_DEPTH; i++) { atTmpBuffer += snprintf(tmpBuffer + atTmpBuffer, sizeof(tmpBuffer) - atTmpBuffer, "tokens_id.data[%d] %d\n", i, data[i]); }
    string result = string(tmpBuffer);
    return result.c_str();
  }
};

static token_ids STOP_SIGNAL = token_ids(FL_STOP_SIGNAL);


// fast binary file header
static constexpr int FleksyCode = ( 42 | (42 << 8) | (42 << 16) | (42 << 24) );  // start code for Fleksy Fast Binary File

struct tagFastBinaryFileHeader
{
  int code;  // id code for Fleksy binary file
  int version;  // version of binary file
  int index_size; // size of index
  int extra_hdr_bytes;  // number of extra header bytes
};
typedef struct tagFastBinaryFileHeader FastBinaryFileHeader;

enum verbosityMode {
  SILENT_MODE = 0,
  SIMPLE_TRACE_MODE,
  DETAILED_TRACE_MODE };

// token prediction type
enum pred_type { bigram = 0,
                 trigram,
                 unigram,
                 unknown
};


typedef list<FLString> list_string;

// forward declaration
class FLSingleLevelTokenPredictor;
class Prediction;
typedef vector<Prediction> list_pred;  // a vector of predictions

class FleksyContextCommon {
  
private:
  static word_id reconstructWordID(unsigned char byte1, unsigned char byte2);

public:
  static pred_type prediction_type;  // whether unigrams, bigrams, or trigrams were used to make the prediction

  static probability maxProb;
  static probability minProbLog;
  static probability maxProbLog;
  static int probsHistogram[256];
  
  static void writeFloat(float f, ofstream& myfile);
  static float readFloat(FLFilePtr &file);

  static size_t writeGolombEncodedData(const GolombEncodingResult& data, ofstream& outfile);
  static size_t writeGolombEncodedData(const GolombEncodingResult& data, unsigned char **buffer, unsigned char *bufferEnd);
  static void readGolombEncodedData(FLFilePtr &file, IntVector& result, size_t elementsToRead = 0);

  static probability decodeProbability(unsigned char z);
  static unsigned char encodeProbability(probability p);
  
  static void writeFloat(float f, unsigned char **buffer, unsigned char *bufferEnd);
  static void writeProbability(probability p, unsigned char **buffer, unsigned char *bufferEnd);
  static void writeWordID(word_id tokenID, unsigned char **buffer, unsigned char *bufferEnd);
  static void writeResultList(const list_pred &pPreds, bool writeIDs, bool writeProbabilities, unsigned char **buffer, unsigned char *bufferEnd);
  static size_t writePredictionsToBuffer(const list_pred &pPreds, unsigned char *predictionsBuffer, unsigned char *predictionsBufferEnd, uint32_t& flagUsed, map<word_id, word_id>& idMap);
  static size_t maxSizeForPredictionList(const list_pred &pPreds);

  // accumulate tokenID counts on a map
  static void addToTokenIDUsageMap(list_pred& preds, map<word_id, int>& results);
  // convert IDs so that ID1 is the most frequenct one and all IDs go in occurence descending order
  static map<word_id, word_id> convertToOptimalUsageMap(map<word_id, int> wordIDCounts);


  static void writeWordID(word_id tokenID, ofstream& myfile);
  static void writeProbability(probability p, ofstream& myfile);
  static void writeTerminatingValue(ofstream& myfile);

  static word_id readWordID(char* data, long& pointer);
  static probability readProbability(char* data, long& pointer);
  
  static word_id readWordID(FLFilePtr &file, bool invert = false);

  //TODO offset typedef. Signed or unsigned?
  static int readOffset(FLFilePtr &file);
  
  static probability readProbability(FLFilePtr &file);
  
  static bool predictionCompare(Prediction p1, Prediction p2);

  static void map_to_list(map_probs& m, list_pred& result);
  static void list_to_map(list_pred& l, map_probs& result);
  static map_probs list_to_rank_map(list_pred& l);
  static void normalizePreds(list_pred& preds);
  static void printPreds(list_pred& preds, token_ids previousTokens, char* (*tokenDescriptionFromID)(word_id), int tag, int limit = 500);
  // fast binary file support code (may be used by FLContextProducer or FLTokenPredictor)
  static FastBinaryFileHeader readFastHdr(FLFilePtr &myfile, char ** phdr_data = nullptr, const char * caller = nullptr);
  //static void readFastBinaryFile(const char * filename, short_lut& alt_table, FLSingleLevelTokenPredictor *pPredictor = NULL);  // read fast binary file into lookup table

  static int nVerbosity;  // verbosity level
  static void combinePreds(list_pred& candidates, list_pred& bi_candidates);

  static void read_temp_unigrams(unordered_map<word_id, probability> &unigram_map, list_pred& unigram_candidates);

  static bool read_unigrams(FLFilePtr &unigramFile, unordered_map<word_id, probability> &map, list_pred &candidates);
  
  static void printFastHdr(FastBinaryFileHeader& hdr);
  
  static size_t addPredictions(list_pred& result, FLFilePtr file, int flag, int count = 0);

  static bool IsNumber(char * str) {
    char *ptr = str;
    while(*ptr) {
      if(!isdigit(*ptr)) { return false; }
      ptr++;
    }
    return true;
  };
friend class FLContextProducer;

};  // class FleksyContextCommon




class Prediction
{
public:
  word_id wordID;
  FLString word;
  probability weight;
  // constructors
  Prediction(word_id shortWordID, probability p, bool occurences = false) {
    if(p <= 0.0f) { throw std::invalid_argument("p <= 0.0"); }
    if(occurences) { if(p < 1.0f) { throwInvalidArgument("p occurence < 1.0", p); } } else { if(p > 1.0f) { throwInvalidArgument("p occurence > 1.0", p); } }
    wordID = shortWordID;
    weight = p;
  };
  // destructors
  ~Prediction() { };
  bool operator<(Prediction& pred) const { return (this->weight < pred.weight); };
  bool operator>(Prediction& pred) const { return (this->weight > pred.weight); };
  
  const char * c_str() {
    char tmpBuffer[128];
    snprintf(tmpBuffer, sizeof(tmpBuffer), "(%s, %f)", word.c_str(), weight);
    string result = string(tmpBuffer);
    return result.c_str();
  }

  friend ostream& operator<<(ostream& out, Prediction& pred) { out << "(" << pred.wordID << ", " << pred.word.c_str() << ", " << pred.weight << ")";  return out; };
    
  // want to find predictions by word
  bool operator==(const Prediction& pred) { return (this->word == pred.word); };  // const Prediction& is critical (error otherwise)
  bool operator!=(const Prediction& pred) { return (this->word != pred.word); };  // const Prediction& is critical (error otherwise)

  static void throwInvalidArgument(const char* message, probability value) { ostringstream msg(message); msg << " (" << value << ")"; throw std::invalid_argument(msg.str()); }
};
    
class FLSmartTokenizer
{
  // class for smart tokenizing
public:
  FLSmartTokenizer();
  FLSmartTokenizer(string separators);
  bool getNextToken(stringstream& ss, string& token);  // smart tokenizer for punctuation
private:
  string separators;
  string head;
  string sep;
  string tail;
};

#endif /* defined(FleksyContext_FleksyContextCommon_h) */
