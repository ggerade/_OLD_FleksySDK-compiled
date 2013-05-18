#ifndef FLTrigramsBin_h
#define FLTrigramsBin_h

#include <sys/syslimits.h>
// Fleksy Headers
#include "FLContextCommon.h"
#include <PatternRecognizer/FLFile.h>

// !!! NO HARDCODED PATHS HERE, DEFINE THOSE IN APPLICATION (eg ContextTester) !!!
#define FL_TRIGRAM_BIN_FILE "binary_files/file3"  // write directly to file3
//#define FL_TRIGRAM_BIN_FILE "binary_files/put.trigram.binary.file.here"

typedef unsigned int BYTE_OFFSET;

class FLTrigramsBin
{
 public:
  FLTrigramsBin(FLFilePtr &); // constructor
  ~FLTrigramsBin();
  static int nVerbosity;

  void getNextCandidatesList(FLFilePtr &tri_file,
                                    list_pred& result, 
                                    token_ids previousTokenIDs, 
                                    int resultsLimit, 
                                    probability pThreshold);

  void getNextCandidatesList(list_pred& result, 
                                    token_ids previousTokenIDs, 
                                    int resultsLimit, 
                                    probability pThreshold);

  // binary file read/write functions
  static unsigned int hash_trigram(word_id wid1, word_id wid2);
  static unsigned int myhash(unsigned int n);
  void readHdr();

  FLFilePtr trigram_bin_file;   // FLFile object for trigram binary file

 private:
  // offsets/sizes for header of binary file
  //
  unsigned int hdr_offset;  // header offset in bytes (size of binary file header)
  unsigned int col_table_size;  // size of the collision table (read from header)

};  // FLTrigramsBin

// hash functions for trigrams

//const unsigned int INDEX_SIZE = (1 << 21) + (1 << 19);  // should be about 2.6 million
const unsigned int   INDEX_SIZE = 2500000;
const unsigned int   OFFSET_SIZE = 4;  // an offset is 4 bytes (32-bit unsigned int)
const unsigned int   ID_SIZE = 2;      // word id code is 2 bytes (16-bit unsigned int)
//const unsigned int INDEX_SIZE = 5000000;
const unsigned int   PREDICTION_SIZE = 3;  // predictions are 3 bytes (2 byte word id, 1 byte weight)

#endif  // FLTrigramsBin_h
