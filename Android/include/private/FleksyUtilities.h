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
  
  FLChar getNearestLetterForPoint(FLPoint& target);

  FLAddWordResult _addWord(const FLString& wordLetters, double frequency, const FLString& printLetters, BBValue uniqueID, bool ignoreBlacklist, bool calculateBlackboxValues);
  void _processWordlistLine1(FLString* wordString, kWordlistType type, const FLString& delimiter, bool calculateBlackboxValues);
  void processWordBlacklistLine(FLString* line, const FLString& delimiter2);
  void processWordlistLine(FLString* wordString, const FLString& delimiter, kWordlistType type, bool calculateBlackboxValues);
  void loadDictionary(const string& filename, void* data, size_t dataLength, const FLString& delimiter, kWordlistType type, bool calculateBlackboxValues, bool isEncrypted);

   
public:
  FleksyUtilities();
  ~FleksyUtilities();
  
  ///////  API  ///////
  FLPoint loadKeyboardData(void* data, size_t dataLength, bool isEncrypted);
  //void preloadWithPathFormat(const string& filepathFormat);
  void preloadWithContents(int wordLength, const void* contents, size_t contentLength);
  void loadDictionary(const string& tag, void* data, size_t dataLength, const FLString& delimiter, kWordlistType type, bool isEncrypted);
  void loadDictionary(FLFile& f, const FLString& delimiter, kWordlistType type, bool isEncrypted);
  void writeTables(const string& filepath); //optional
  void postload();
  FLInternalSuggestionsContainer* processWord(FLWord* inputWord, FLString* rawText, FLWordList& hints);
  FLAddWordResult addWord(const FLString& word, float frequency);
  bool removeWord(const FLString& wordLetters);
  ////////////////////
  
  FLKeyboard keyboard;
  
  size_t loadedWordCount();
  bool isWordInDictionary(const FLString& printLetters, bool allowLowerCase);
  FLWord* getWordByString(const FLString& s, bool allowLowerCase = false);
  //FLWord* getRandomWord(int length);
  FLPoint* pointsFromLetters(const FLString& letters);
  FLString lettersFromPoints(FLPoint* points, short nPoints);
  FLPoint getPointForChar(FLChar c, FLKeyboardID keyboardID);
  float getDistanceBetweenLetters(FLChar c1, FLChar c2);
  
  
  FLWordDatabase* getWordDatabase();
  bool getLoadedPreprocessedFiles();
  bool getPostloaded();
  
};

#endif
