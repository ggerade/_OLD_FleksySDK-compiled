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
//#include <map>
#include <unordered_map>
#include <list>
// ANSI C Headers for C++
#include <cassert>

// Fleksy headers
//#include <PatternRecognizer/Structures.h>
#include "PatternRecognizer/Platform.h"
#include "TimeFunctions.h"

class triPrediction;

//#define FLassert(__CONDITION__) assert(__CONDITION__)

#define MAX_WORD_ID 65000
#define MAX_WORD_DEPTH 2  // was 2 (jfm)

// max count of trace messages reported by functions
// once function has been called FL_MAX_COUNT times, it goes silent
const unsigned int FL_MAX_COUNT = 5;  // default to zero (set to non-zero such as 5 for trace debuggin)
const unsigned int FL_COCA_SIZE = 420170105;  // think this is the number of words in the Mark Davies COCA corpus (our training set)  -- jfm
const unsigned int FL_SIGNIFICANT_COUNT = 100; // was 20; // used to determine whether the absence of a trigram or bigram gives statistically signficant information on the probability of the bigram or trigram.  If unigram frequency predicts a count above this value, then lack of unigram/bigram gives information -- use 0 prob estimate in this case.
const unsigned int FL_MAX_CANDIDATES = 1000;  // maximum number of candidates returned (for unigrams right now)
const double       FL_UNI_SCALE = 0.1;  // max range for unigram probability (bit larger than probability of "the")
const unsigned int FL_READ_REPORT = 20000;  // report read info every FL_READ_REPORT reads (when FL_FLEKSY_TRACE set)
const int FL_STOP_SIGNAL = -1;   // code to stop threads

using namespace std;

typedef int word_id;
typedef float probability;
typedef unordered_map<word_id, probability> map_probs;
typedef struct short_lut { map_probs data[MAX_WORD_ID]; } short_lut;

class token_ids { 
public:
  word_id data[MAX_WORD_DEPTH];
  bool bActive[MAX_WORD_DEPTH];  // flag to indicate the token is active
  bool operator==(token_ids& rhs)
  {
    for(int i = 0; i < MAX_WORD_DEPTH; i++)
    {
      if(data[i] != rhs.data[i])
        return false;

      if(bActive[i] != rhs.bActive[i])
        return false;
    }
    return true;
  } // operator==

  bool operator!=(token_ids& rhs)
  {
    for(int i = 0; i < MAX_WORD_DEPTH; i++)
    {
      if(data[i] != rhs.data[i])
        return true;

      if(bActive[i] != rhs.bActive[i])
        return true;
    }

    return false;  // they are equal

  }  // operator!=

  token_ids()  // constructor
  {
    for(int i = 0; i < MAX_WORD_DEPTH; i++)
    {
      data[i] = 0;
      bActive[i] = false;
    }
  }

  // assignment operator
  // The assignment operator is used to copy the values from one object to another already existing object. 
  // The key words here are “already existing”.
  // e.g.
  // token_ids old_tokens1, old_tokens2;
  // old_tokens2 = old_tokens1;
 
  token_ids& operator= (const token_ids &rhs)
    {
      if(this == &rhs)
        return *this;

      for(int i = 0; i < MAX_WORD_DEPTH; i++)
      {
        data[i] = rhs.data[i];
        bActive[i] = rhs.bActive[i];
      }

      return *this;
    }

  bool operator== (int n)  // for stop signal
  {
    for(int i = 0; i < MAX_WORD_DEPTH; i++)
    {
      if (data[i] != n)
        return false;
    }

    return true;
  }

  // copy constructor
  // A copy constructor is a special constructor that initializes a new object from an existing object.
  // e.g. token_ids new_tokens = old_tokens;

  token_ids(const token_ids& rhs)
  {
    // check for self-assignment

    for(int i = 0; i < MAX_WORD_DEPTH; i++)
    {
      data[i] = rhs.data[i];
      bActive[i] = rhs.bActive[i];
    }
  }  // copy constructor

  // print method
  void print()
  {
    // problem with thread safety in cout
    //
    for(int i = 0; i < MAX_WORD_DEPTH; i++)
    {
      LOGI("tokens_id.data[%d] %d  tokens_id.bActive[%d] %d\n", i, data[i], i, bActive[i] );
    }
    fflush(stdout);
  }  // print

  // special constructor
  token_ids(int n)
  {
    for(int i = 0; i < MAX_WORD_DEPTH; i++)
    {
      data[i] = n;
      bActive[i] = true;
    }
  }  // create token_ids with non-default values

  void shift(word_id wid, bool bActiveNew = true)
  {
    int i = 0;

    for(i = (MAX_WORD_DEPTH-1); i > 0; i--)
    {
      data[i] = data[i-1];
      //
      bActive[i] = bActive[i-1];
    }

    data[0] = wid;
    bActive[0] = bActiveNew;
  }

  char * c_str()
  {
    char szBuf[80];
    char * result = new char[MAX_WORD_DEPTH*80];

    for(int i = 0; i < MAX_WORD_DEPTH; i++)
    {
      snprintf(szBuf, sizeof(szBuf), "tokens_id.data[%d] %d  tokens_id.bActive[%d] %d\n", i, data[i], i, bActive[i] );
      strncat(result, szBuf, MAX_WORD_DEPTH*80);
    }    

    return result;
  } // c_str()

};  // class token_ids

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

static bool tokensAreEqual(token_ids& tokens1, token_ids& tokens2) {
  for (int i = 0; i < MAX_WORD_DEPTH; i++) {
    if (tokens1.data[i] != tokens2.data[i]) {
      return false;
    }
  }
  return true;
}

typedef list<FLString> list_string;

// forward declaration
class FLSingleLevelTokenPredictor;
class Prediction;
typedef vector<Prediction> list_pred;  // a vector of predictions

// TODO: do we need both list_pred and map_probs?

// data type for table of predictions
typedef unordered_map<FLString, list_pred*> Predictions;

class FLContextProducer; // forward declaration

class FleksyContextCommon {
public:
  static pred_type prediction_type;  // whether unigrams, bigrams, or trigrams were used to make the prediction
  // unigram binary file name setter/getters
  static void set_unigram_binary_file(char * in) { strncpy(szUniBinFile, in, PATH_MAX); assert(strlen(szUniBinFile) == strlen(in)); };
  static void set_uni_bin_file(char * in) { set_unigram_binary_file(in); };
  static void set_uni_bin(char * in) { set_unigram_binary_file(in); };
  static const char * get_unigram_binary_file() { return (const char *) szUniBinFile; };
  static const char * get_uni_bin_file() { return get_unigram_binary_file(); };
  
  static probability minProbLog;
  static probability maxProbLog;
  
  static void writeWordID(word_id tokenID, ofstream& myfile);
  static void writeProbability(probability p, ofstream& myfile);
  static void writeTerminatingValue(ofstream& myfile);

  static word_id reconstructWordID(unsigned char byte1, unsigned char byte2);
  static word_id readWordID(const char* data, long& pointer);
  static probability readProbability(unsigned char z);
  static probability readProbability(const char* data, long& pointer);
  
  static bool predictionCompare(Prediction p1, Prediction p2);

  static list_pred map_to_list(map_probs& m);
  static map_probs list_to_map(list_pred& l);
  static map_probs list_to_rank_map(list_pred& l);
  static void normalizePreds(list_pred& preds);
  static void printPreds(list_pred& preds, token_ids previousTokens, char* (*tokenDescriptionFromID)(word_id), int tag, int limit = 500);
  // fast binary file support code (may be used by FLContextProducer or FLTokenPredictor)
  static FastBinaryFileHeader readFastHdr(string fast_bin_file, char** phdr_data = NULL, const char * caller = NULL);
  static void readFastBinaryFile(const char * filename, short_lut& alt_table, FLSingleLevelTokenPredictor *pPredictor = NULL);  // read fast binary file into lookup table

  static int nVerbosity;  // verbosity level
  static void combinePreds(list_pred& candidates, list_pred& bi_candidates);

  static void read_uni_bin(string uni_bin_file, unordered_map<word_id, double> &unigram_map, list_pred& unigram_candidates);
  static void printFastHdr(FastBinaryFileHeader& hdr);

  static bool IsNumber(char * str) {
    char * ptr = str;
    while(*ptr) {
      if( !isdigit(*ptr) )
        return false;
      ptr++;
    }
    return true;
  };

private:
  static char szUniBinFile[PATH_MAX];  // file name for unigrams binary file
};  // class FleksyContextCommon

class Prediction
{
public:
  word_id wordID;
  FLString word;
  probability weight;
  // constructors
  Prediction(word_id shortWordID, probability p) { assert(p); wordID = shortWordID, weight = p; };
  //Prediction() { word = FLStringMake(""); weight = 0.0; };
  Prediction(FLString& str, double wt) {  assert(wt); word = str; weight = wt; };
  // destructors
  ~Prediction() { };
  bool operator<(Prediction& pred) const { return (this->weight < pred.weight); };
  bool operator>(Prediction& pred) const { return (this->weight > pred.weight); };
  
  char * c_str() { 
    char * ptr = new char[128];
    snprintf(ptr, 128, "(%s, %f)", word.c_str(), weight);
    return ptr;
  }
  friend ostream& operator<<(ostream& out, Prediction& pred) { 
    out << "(" << pred.wordID << ", " << pred.word.c_str() << ", " << pred.weight << ")";  return out; };
    
  // want to find predictions by word
  bool operator==(const Prediction& pred) { return (this->word == pred.word); };  // const Prediction& is critical (error otherwise)
  bool operator!=(const Prediction& pred) { return (this->word != pred.word); };  // const Prediction& is critical (error otherwise)

  bool operator==(const triPrediction& pred); //  { return ( string( (char *) this->word.c_str() ) == pred.word); };  // const Prediction& is critical (error otherwise)
  bool operator!=(const triPrediction& pred); //  { return ( string( (char *) this->word.c_str() ) != pred.word); };  // const Prediction& is critical (error otherwise)

};
    
// function declarations
void display_pred_table(Predictions& pred_table);
Predictions* read_pred_table(string& fname);

string where_am_i();  // string& can cause problems -- return by value

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
