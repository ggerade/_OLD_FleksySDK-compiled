#ifndef FLTrigramsBin_h
#define FLTrigramsBin_h

#include <sys/syslimits.h>
// Fleksy Headers
#include "FLContextCommon.h"
#include <PatternRecognizer/FLFile.h>

typedef unsigned int BYTE_OFFSET;

class FLTrigramsBin
{
 public:
  FLTrigramsBin(FLFile *);
  ~FLTrigramsBin();
  static int nVerbosity;

  void getNextCandidatesList(list_pred& result, 
                                    token_ids previousTokenIDs, 
                                    int resultsLimit, 
                                    probability pThreshold);

  // binary file read/write functions
  static unsigned int hash_trigram(word_id wid1, word_id wid2);
  static unsigned int myhash(unsigned int n);
  void readHdr();

//  static void set_hdr_offset(unsigned int offset) { hdr_offset = offset; };
//  static unsigned int get_hdr_offset() { return hdr_offset; };
//
//  static void set_col_table_size(unsigned int size) { col_table_size = size; };
//  static unsigned int get_col_table_size() { return col_table_size; };
//
//  static void add_extra_bytes(char * data, int nBytes) 
//  { 
//    extra_bytes = new char[nBytes];
//    for(int i=0; i < nBytes; i++)
//      extra_bytes[i] = data[i];
//
//    set_hdr_offset(sizeof(FastBinaryFileHeader) + 4 + nBytes);
//  }
//
//  static char *extra_bytes;
  
 private:
  FLFile* trigram_bin_file;
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
