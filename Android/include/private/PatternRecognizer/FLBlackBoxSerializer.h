//
//  FLBlackBoxSerializer.h
//  PatternRecognizer
//
//  Created by Kostas Eleftheriou on 6/25/12.
//  Copyright (c) 2012 Syntellia Inc. All rights reserved.
//

#include "FLBlackBox.h"
#include <string>

using namespace std;

class FLBlackBoxSerializer {
public:
  static char* memoryMapFile(const char* filepath, size_t* outLength);
  static void unmapMemoryMapFile(void* data, size_t length);

  static void writeTable(FLBlackBox& table, const string filepath);
  static size_t loadTableWithPath(const string filepath, FLBlackBox& result);
  static size_t loadTableWithContents(const char* contents, size_t length, FLBlackBox& result);
};
