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
public:
  FleksyAPIpImpl(FleksyListenerInterface &listener, bool simulateSystemCursorUpdates = false);
  ~FleksyAPIpImpl();
  FleksyListenerInterface &out;
  FLTypingController *tc;
  SystemsIntegrator* fleksy;
  string resourcePath;
  FLResourceArchive *resourceArchive = NULL;
  // set this to have preprocessed files generated. Do not add "/" in the end.
  string writableDirectory;
  bool isEngineLoaded;
  void setMaxNumberOfSuggestions(int numberOfSuggestions);
  void loadKeyMaps();
  void postLoadSetup();
  void loadKeyboardData(void* characterCoordinates, int charCoordinatesLength);
  void loadPreprocessedFile(int wordLength, const void* preprocessedFile, int preprocessedFileLength);
  void setResourceFLFile(FLFile* file);
  void initialize(FLFile* preloaded, FLFile* wordlist, FLFile* blackListCapital, FLFile* blackList, string unigramFile, string bigramFile, string trigramFile, bool isEncrypted = true);
};

#endif
