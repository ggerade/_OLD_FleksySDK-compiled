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
  FLTrigramsBin(FLFilePtr &trigramsBinFile); // constructor
  ~FLTrigramsBin();

  void getNextCandidatesList(list_pred &result, token_ids previousTokenIDs, int resultsLimit, probability pThreshold);

  // binary file read/write functions
  static unsigned int hash_trigram(word_id wid1, word_id wid2);
  static unsigned int myhash(unsigned int n);

 private:
  void readHdr();

  FLFilePtr trigram_bin_file;   // FLFile object for trigram binary file

  // offsets/sizes for header of binary file
  //
  int _fileVersion = 0;
  size_t _hashTableSlots = 0;
  const uint32_t *_hashTable = NULL;
  const unsigned char *_predictions = NULL;
  const unsigned char *_fileContents = NULL;
};  // FLTrigramsBin

// hash functions for trigrams

const unsigned int   OFFSET_SIZE = 4;  // an offset is 4 bytes (32-bit unsigned int)

#endif  // FLTrigramsBin_h
