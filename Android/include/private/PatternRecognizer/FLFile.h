//
//  FLFile.h
//  FleksyLib
//
//  Created by Kosta Eleftheriou on 4/22/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FLFILE_HEADER
#define FLFILE_HEADER

#include <iostream>
#include <iosfwd>
#include <memory>
#include "FLUnicodeString.h"
#include "FLException.h"
#include "EncryptionUtilities.h"

#define USE_MEMORY_MAP 1

namespace Fleksy {
  class EXPORT FileException : public Fleksy::Exception {
  public:
    explicit FileException(std::string message, std::string filename = "", int lineNumber = 0) {
      init(message, filename, lineNumber);
    }
  };
}

class FLFile;
typedef std::shared_ptr<FLFile> FLFilePtr;

class FLFile {

private:
  
  int fileID;
  
  FLFilePtr parent;
  ////////////////
  
  FLUnicodeString tag;
  
  // see if we really need this other than for grabbing the file size when constructed from a file path
  int fd = -1;
  off_t startOffset = 0;
  off_t currentRelativeOffset = 0;
  size_t length = 0;
  
  void* contents = NULL;
  
  bool    memoryMapped        = false;
  void   *memoryMappedAddress = NULL;
  size_t  memoryMappedLength  = 0;
  
  void init(off_t _startOffset, size_t *_length, FLFilePtr *parent);
  void cleanup();

  void* getContentsWithOffset(off_t offset);
  
  
//////////////////
public:
  
  // File path constructor
  FLFile(FLUnicodeString filepath);
  
  // File descriptor constructor
  // startOffset and length are for Android where we may get different FDs on the same file (the APK)
  FLFile(int fileDescriptor, off_t startOffset = 0, size_t length = 0);
  
  // Parent FLFile constructor
  FLFile(FLFilePtr &_parent, FLUnicodeString tag, off_t startOffset, size_t _length);

  // Parent FLFile "copy constructor"
  FLFile(FLFilePtr &_parent);

  
  void read(void* outBuffer, size_t length);
  std::vector<FLUnicodeString> getLines(bool decrypt = true, bool decompress = false, const char * key = DEFAULT_M_VALUE);
  
  // offset is relative from begining of file
  void seek(off_t offset);
  
  off_t tellg();
  
  bool is_open();
  bool good();
  
  
  
  void* getContents(bool memoryMapped = USE_MEMORY_MAP);
  size_t getLength();
  FLUnicodeString getTag();
  
  ~FLFile();
};

#endif /* defined(FLFILE_HEADER) */
