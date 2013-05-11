//
//  FLFile.h
//  FleksyLib
//
//  Created by Kosta Eleftheriou on 4/22/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FLFILE_HEADER
#define FLFILE_HEADER

#define FLFILE_FLATTEN_FOR_INLINE_OPTIMIZATION 0

#include <iostream>
#include <iosfwd>

#define USE_MEMORY_MAP 1

using namespace std;

class FLFile {

private:
  
  int fileID;
  
  FLFile* parent = NULL;
  int childCount = 0;
  ////////////////
  
  string tag;
  
  // see if we really need this other than for grabbing the file size when constructed from a file path
  int fd = -1;
  off_t startOffset = 0;
  off_t currentRelativeOffset = 0;
  size_t length = 0;
  
  void* contents = NULL;
  
  bool memoryMapped = false;
  
  void init(off_t _startOffset, size_t *_length, FLFile* parent);
  void* getContentsWithOffset(off_t offset);
  
  
//////////////////
public:
  
  // File path constructor
  FLFile(string filepath);
  
  // File descriptor constructor
  // startOffset and length are for Android where we may get different FDs on the same file (the APK)
  FLFile(int fileDescriptor, off_t startOffset = 0, size_t length = 0);
  
  // Parent FLFile constructor
  FLFile(FLFile* _parent, string tag, off_t startOffset, size_t _length);

  // Parent FLFile "copy constructor"
  FLFile(FLFile* _parent);

  
  void read(char* outBuffer, size_t length);
  
  // offset is relative from begining of file
  void seek(off_t offset);
  
  off_t tellg();
  
  bool is_open();
  bool good();
  
  
  
  void* getContents(bool memoryMapped = USE_MEMORY_MAP);
  size_t getLength();
  string getTag();
  
  ~FLFile();
};

#if FLFILE_FLATTEN_FOR_INLINE_OPTIMIZATION
#include "FLFile.cpp"
#endif

#endif /* defined(FLFILE_HEADER) */
