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
  
  static int nFiles;
  
  int fileID;
  
  FLFile* parent;
  int childCount;
  ////////////////
  
  string tag;
  
  // see if we really need this other than for grabbing the file size when constructed from a file path
  FILE* file = NULL;
  int fd;
  off_t startOffset;
  off_t currentRelativeOffset;
  size_t length;
  
  void* contents = NULL;
  
  bool memoryMapped;
  
  void init(off_t _startOffset, size_t _length, FLFile* parent);
  void* getContentsWithOffset(off_t offset);
  void runTest();
  
  
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
  
  bool is_open();
  bool good();
  
  
  
  void* getContents(bool memoryMapped = USE_MEMORY_MAP);
  size_t getLength();
  string getTag();
  
  ~FLFile();
};

#endif /* defined(__FleksyLib__FLFile__) */
