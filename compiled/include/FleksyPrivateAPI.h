//
//  FleksyPrivateAPI.h
//  FleksyLib
//
//  Created by Vadim Maximov on 3/22/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FleksyLib_FleksyPrivateAPI_h
#define FleksyLib_FleksyPrivateAPI_h

class FLTypingController;
class SystemsIntegrator;

class FleksyAPIpImpl{
public:
  FleksyAPIpImpl(FleksyListenerInterface &listener, bool simulateSystemCursorUpdates = false);
  FleksyListenerInterface &out;
  FLTypingController *tc;
  SystemsIntegrator* fleksy;
  string resourcePath;
  bool isEngineLoaded;
  void loadKeyMaps();
  void postLoadSetup();
  void loadKeyboardData(void* characterCoordinates, int charCoordinatesLength);
  void loadPreprocessedFile(int wordLength, char* preprocessedFile, int preprocessedFileLength);
  void initialize(void* preloaded, int preloadedLength, void* wordlist, int wordlistLength,
                  void* blackListCapital, int blackListCapitalLength, void* blackList, int blackListLength, void* userWordList, int userWordListLength, string unigramFile, string bigramFile, string trigramFile, bool isEncrypted = true);
};


#endif
