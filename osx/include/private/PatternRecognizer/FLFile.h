//
//  FLFile.h
//  FleksyLib
//
//  Created by Kosta Eleftheriou on 4/22/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksyLib__FLFile__
#define __FleksyLib__FLFile__

#include <iostream>
#include <iosfwd>

#define USE_MEMORY_MAP 1

using namespace std;

class FLFile {

private:
  
  FLFile* parent;
  int childCount;
  ////////////////
  
  string filepath;
  
  FILE* file;
  int fd;
  off_t startOffset;
  size_t length;
  
  void* contents;
  
  bool memoryMapped;
  
  void init(off_t _startOffset, size_t _length, FLFile* parent);
  void* getContentsWithOffset(bool memoryMapped, off_t offset);
  
  
//////////////////
public:
  
  // File path constructor
  FLFile(string filepath);
  
  // File descriptor constructor
  // startOffset and length are for Android where we may get different FDs on the same file (the APK)
  FLFile(int fileDescriptor, off_t startOffset = 0, size_t length = 0);
  
  // Parent FLFile constructor
  FLFile(FLFile* _parent, string tag, off_t startOffset, size_t _length);

  // TODO methods to "seek" and read (for context)
  //void reset();
  //void read(char* out, size_t length);
  
  void* getContents(bool memoryMapped = USE_MEMORY_MAP);
  size_t getLength();

  
  ~FLFile();
};

#endif /* defined(__FleksyLib__FLFile__) */
