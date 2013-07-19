//
//  FleksyUtilities.h
//  PatternRecognizer
//
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#ifndef FLEKSY_UTILITIES_H
#define FLEKSY_UTILITIES_H

//#include <PatternRecognizer/PatternRecognizer.h>

#include <PatternRecognizer/FLInternalSuggestionsContainer.h>
#include <PatternRecognizer/FLBlackBox.h>
#include <PatternRecognizer/FLWordDatabase.h>
#include <PatternRecognizer/FLVotesHolder.h>
#include <PatternRecognizer/FLFile.h>
#include "FLKeyboard.h"
#include "FleksyDefines.h"
#include <map>

#define DEFAULT_USER_WORD_FREQUENCY 15000

using namespace std;

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
  
  bool loadedPreprocessedFiles[FLEKSY_MAX_WORD_SIZE+1]; //1-based index TODO switch to 0
  bool postLoaded;
  
  FLAddWordResult _addWord(FLStringPtr &wordLetters, FLStringPtr &printLetters, BBValue uniqueID, bool ignoreBlacklist, bool calculateBlackboxValues, bool canBeRemoved);
  void _processWordlistLine1(FLString* wordString, kWordlistType type, const FLString& delimiter, bool calculateBlackboxValues);
  void processWordBlacklistLine(FLString* line, const FLString& delimiter2);
  void processWordlistLine(FLString* wordString, const FLString& delimiter, kWordlistType type, bool calculateBlackboxValues);
  void loadDictionary(const string& filename, void* data, size_t dataLength, const FLString& delimiter, kWordlistType type, bool calculateBlackboxValues, bool isEncrypted);

   
public:
  FleksyUtilities();
  ~FleksyUtilities();
  
  ///////  API  ///////
  //void preloadWithPathFormat(const string& filepathFormat);
  void preloadWithContents(int wordLength, const void* contents, size_t contentLength);
  void loadDictionary(const string& tag, void* data, size_t dataLength, const FLString& delimiter, kWordlistType type, bool isEncrypted);
  void loadDictionary(FLFilePtr &f, const FLString& delimiter, kWordlistType type, bool isEncrypted);
  void writeTables(const string& filepath); //optional
  void postload();
  FLInternalSuggestionsContainer* processWord(const FLWord* inputWord, FLWordList& hints);
  FLAddWordResult addWord(FLStringPtr &word, bool canBeRemoved);
  bool removeWord(FLStringPtr &wordLetters);
  ////////////////////
  
  FLKeyboardPtr keyboard;
  FLPoint loadKeyboardData(FLFilePtr &keyboardFile, bool isEncrypted);
  
  size_t loadedWordCount();
  bool isWordInDictionary(FLStringPtr &printLetters, bool allowLowerCase);
  FLWordPtr getWordByString(FLStringPtr &s, bool allowLowerCase = false);
  FLWordPtr getWordByID(int wordID);
  //FLWord* getRandomWord(int length);
  
  
  FLWordDatabase* getWordDatabase();
  bool getLoadedPreprocessedFiles();
  bool getPostloaded();
  
};

#endif
