//
//  FleksyPrivateAPI.h
//  FleksyLib
//
//  Created by Vadim Maximov on 3/22/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FleksyLib_FleksyPrivateAPI_h
#define FleksyLib_FleksyPrivateAPI_h

#include "FLFile.h"
#include "FLResourceArchive.h"

class FLTypingController;
class SystemsIntegrator;

class FleksyAPIpImpl{
private:
  FLFile *resourceArchiveFile = NULL;
  FLResourceArchive *resourceArchive = NULL;
  string resourcePath;
  
  FLFile* unigramFile;
  FLFile* bigramFile;
  FLFile* trigramFile;
  
public:
  FleksyAPIpImpl(FleksyListenerInterface &listener, bool simulateSystemCursorUpdates = false);
  ~FleksyAPIpImpl();
  FleksyListenerInterface &out;
  FLTypingController *tc;
  SystemsIntegrator* fleksy;
  // set this to have preprocessed files generated. Do not add "/" in the end.
  string writableDirectory;
  bool isEngineLoaded;
  string getResourceDescription();
  void setMaxNumberOfSuggestions(int numberOfSuggestions);
  void loadKeyMaps();
  void postLoadSetup();
  void loadKeyboardData();
  void loadPreprocessedFile(int wordLength, const void* preprocessedFile, size_t preprocessedFileLength);
  void setResourceFLFile(FLFile* file);
  void setResourcePath(string path);
  FLFile* FLFileForFileName(const char *filename);
  void initialize(FLFile* preloaded, FLFile* wordlist, FLFile* blackListCapital, FLFile* blackList, bool isEncrypted = true);
};

#endif
