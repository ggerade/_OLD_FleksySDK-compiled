//
//  FleksyUtilities.h
//  PatternRecognizer
//
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#ifndef FLEKSY_UTILITIES_H
#define FLEKSY_UTILITIES_H

#include <map>
#include <PatternRecognizer/FLWordDatabase.h>
#include <PatternRecognizer/FLFile.h>
#include "FLKeyboard.h"
#include "FleksyDefines.h"
#include "FLTapsToWords.h"
#include "FLUnicodeString.h"

typedef enum {
  FLAddWordResultAdded,
  FLAddWordResultExists,
  FLAddWordResultTooLong,
  FLAddWordResultWordIsBlacklisted,
  FLAddWordResultError
} FLAddWordResult;

typedef enum {
  kWordlistStandard,
  kWordlistPreloaded, // will calculate blackbox values on the fly
  kWordlistUser, // will calculate blackbox values on the fly
  kWordlistBlacklist
} kWordlistType;

class FleksyUtilities {
private:
  FLWordDatabase* wordDatabase;
  
  bool postLoaded;
  
  FLAddWordResult _addWord(FLUnicodeStringPtr &wordLetters, FLUnicodeStringPtr &printLetters, bool ignoreBlacklist, bool canBeRemoved);
  void _processWordlistLine1(FLUnicodeString* wordString, kWordlistType type, const FLUnicodeString& delimiter);
  void processWordBlacklistLine(FLUnicodeString* line, const FLUnicodeString& delimiter2);
  void processWordlistLine(FLUnicodeString* wordString, const FLUnicodeString& delimiter, kWordlistType type);

public:
  FleksyUtilities();
  ~FleksyUtilities();

  FLTapsToWordsPtr tapsToWords;
  
  ///////  API  ///////
  void loadDictionary(const std::string& tag, void* data, size_t dataLength, const FLUnicodeString& delimiter, kWordlistType type, bool isEncrypted);
  void loadDictionary(FLFilePtr &f, const FLUnicodeString& delimiter, kWordlistType type, bool isEncrypted);
  void postload();
  FLAddWordResult addWord(FLUnicodeStringPtr &word, bool canBeRemoved);
  bool removeWord(FLUnicodeStringPtr &wordLetters);
  ////////////////////
  
  FLKeyboardPtr keyboard;
  FLPoint loadKeyboardData(FLFilePtr &keyboardFile, bool isEncrypted);
  
  size_t loadedWordCount();
  bool isWordInDictionary(FLUnicodeStringPtr &printLetters, bool allowLowerCase);
  FLWordPtr getWordByString(FLUnicodeStringPtr &s, bool allowLowerCase = false);
  FLWordPtr getWordPtrByID(int wordID);
  
  FLWordDatabase* getWordDatabase();
  bool getPostloaded();
  
  kLanguage language = kLanguageUnknown;
};

#endif
