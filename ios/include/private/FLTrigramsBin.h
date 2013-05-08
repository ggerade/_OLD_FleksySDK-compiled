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
  ~FLTrigramsBin();
  // !!! NO EMPTY CONSTRUCTOR !!!
  //static FLTrigramsBin* getInstance();
  static FLTrigramsBin* getInstance(FLFile *);
  static int nVerbosity;

  static void getNextCandidatesList(FLFile * tri_file,
                                    list_pred& result, 
                                    token_ids previousTokenIDs, 
                                    int resultsLimit, 
                                    probability pThreshold);

  static void getNextCandidatesList(list_pred& result, 
                                    token_ids previousTokenIDs, 
                                    int resultsLimit, 
                                    probability pThreshold);

  static void set_trigram_binary_file(char * in) { strncpy(szTrigramBinFile, in, PATH_MAX); assert(strlen(szTrigramBinFile) == strlen(in)); };
  static void set_tri_bin_file(char * in) { set_trigram_binary_file(in); };
  static void set_tri_bin(char * in) { set_trigram_binary_file(in); };
  static const char * get_tri_bin_file() { return (const char *) szTrigramBinFile; };
  static const char * get_trigram_binary_file() { return get_tri_bin_file(); };
  static const char * get_tri_bin() { return get_tri_bin_file(); };
  // binary file read/write functions
  static unsigned int hash_trigram(word_id wid1, word_id wid2);
  static unsigned int myhash(unsigned int n);
  static void readHdr();

  static void set_hdr_offset(unsigned int offset) { hdr_offset = offset; };
  static unsigned int get_hdr_offset() { return hdr_offset; };

  static void set_col_table_size(unsigned int size) { col_table_size = size; };
  static unsigned int get_col_table_size() { return col_table_size; };

  static void add_extra_bytes(char * data, int nBytes) 
  { 
    extra_bytes = new char[nBytes];
    for(int i=0; i < nBytes; i++)
      extra_bytes[i] = data[i];

    set_hdr_offset(sizeof(FastBinaryFileHeader) + 4 + nBytes);
  }

  static char *extra_bytes;
  static FLFile * trigram_bin_file;   // FLFile object for trigram binary file

 private:
  // !!! NO EMPTY CONSTRUCTOR !!!
  //FLTrigramsBin();  // constructor
  FLTrigramsBin(FLFile *); // constructor
  static FLTrigramsBin * instance;
  static unsigned int instance_count;  // count of instances of FLTrigramsBin
  static char szTrigramBinFile[PATH_MAX];
  // offsets/sizes for header of binary file
  //
  static unsigned int hdr_offset;  // header offset in bytes (size of binary file header)
  static unsigned int col_table_size;  // size of the collision table (read from header)

};  // FLTrigramsBin

// hash functions for trigrams

//const unsigned int INDEX_SIZE = (1 << 21) + (1 << 19);  // should be about 2.6 million
const unsigned int   INDEX_SIZE = 2500000;
const unsigned int   OFFSET_SIZE = 4;  // an offset is 4 bytes (32-bit unsigned int)
const unsigned int   ID_SIZE = 2;      // word id code is 2 bytes (16-bit unsigned int)
//const unsigned int INDEX_SIZE = 5000000;
const unsigned int   PREDICTION_SIZE = 3;  // predictions are 3 bytes (2 byte word id, 1 byte weight)

#endif  // FLTrigramsBin_h
