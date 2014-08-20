//
//  FleksyUtilities.h
//  PatternRecognizer
//
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#ifndef FLEKSY_UTILITIES_H
#define FLEKSY_UTILITIES_H

#include <map>
#include <PatternRecognizer/FLFile.h>
#include "FLKeyboard.h"
#include "FleksyDefines.h"
#include "FLUnicodeString.h"

class FLTapsToWords;
typedef std::shared_ptr<FLTapsToWords> FLTapsToWordsPtr;

typedef enum {
  FLAddWordResultAdded,
  FLAddWordResultExists,
  FLAddWordResultTooLong,
  FLAddWordResultError
} FLAddWordResult;

typedef enum {
  kWordlistStandard,
  kWordlistPreloaded, // will calculate blackbox values on the fly
  kWordlistUser       // will calculate blackbox values on the fly
} kWordlistType;

class FleksyUtilities {
private:
  bool postLoaded;
  
  void _processWordlistLine1(FLUnicodeString* wordString, kWordlistType type, const FLUnicodeString& delimiter);
  void processWordlistLine(FLUnicodeString* wordString, const FLUnicodeString& delimiter, kWordlistType type);

public:
  FleksyUtilities();

  FLTapsToWordsPtr tapsToWords;
  
  void postload();
  bool getPostloaded();
  void setUseAllAccents(bool use);
  
  std::shared_ptr<FLKeyboard> keyboard;
  void loadKeyboardData(FLFilePtr &keyboardFile, FLFilePtr &commonData);
  
  bool isWordInDictionary(const FLUnicodeString &printLetters, bool allowLowerCase);
  FLDictionaryWordType getDictionaryWordType(const FLUnicodeString &key, bool allowLowerCase);
};

#endif
