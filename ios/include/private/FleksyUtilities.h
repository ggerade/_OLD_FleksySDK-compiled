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
#include "FleksyDefines.h"
#include <map>

#define DEFAULT_USER_WORD_FREQUENCY 15000

using namespace std;

#define INIT_POINTS(__array__) for (int _zz = 0; _zz < KEY_MAX_VALUE; _zz++) { __array__[_zz] = FLPointMake(-1, -1);}

#define KEYBOARD_TAG_ABC_LOWER 0
#define KEYBOARD_TAG_ABC_UPPER 1
#define KEYBOARD_TAG_SYMBOLS1  2
#define KEYBOARD_TAG_SYMBOLS2  3

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
  
  map<int, FLWordList*> wordsByLength; // length 0 holds special non-words like "." and ","
  map<FLString, FLWord*> _wordsByLetters; // renamed with underscore to enforce method get+set and avoid direct [] operator which may create keys that didn't exist
 
  //wordsbyprintletters ????
  
  map<FLString, FLString> wordsBlacklistByLetters;

  
  bool loadedPreprocessedFiles[FLEKSY_MAX_WORD_SIZE+1]; //1-based index TODO switch to 0
  bool postLoaded;
  
  FLChar getNearestLetterForPoint(FLPoint& target);
  bool isWordInBlacklist(const FLString& printLetters);
  //
  FLWord* getWordFromDictionary(const FLString& key);
  void setWordInDictionary(const FLString& key, FLWord* word);
  void deleteWordFromDictionary(const FLString& key);
  //
  FLAddWordResult _addWord(const FLString& wordLetters, double frequency, const FLString& printLetters, BBValue uniqueID, bool ignoreBlacklist, bool calculateBlackboxValues);
  void _processWordlistLine1(FLString* wordString, kWordlistType type, const FLString& delimiter, bool calculateBlackboxValues);
  void processWordBlacklistLine(FLString* line, const FLString& delimiter2);
  void processWordlistLine(FLString* wordString, const FLString& delimiter, kWordlistType type, bool calculateBlackboxValues);
  void loadDictionary(const string& filename, void* data, size_t dataLength, const FLString& delimiter, kWordlistType type, bool calculateBlackboxValues, bool isEncrypted);

   
public:
  FleksyUtilities();
  ~FleksyUtilities();
  
  FLWordList* allWords;
  
  ///////  API  ///////
  void loadKeyboardData(void* data, size_t dataLength, bool isEncrypted);
  //void preloadWithPathFormat(const string& filepathFormat);
  void preloadWithContents(int wordLength, const char* contents, size_t contentLength);
  void loadDictionary(const string& tag, void* data, size_t dataLength, const FLString& delimiter, kWordlistType type, bool isEncrypted);
  void writeTables(const string& filepath); //optional
  void postload();
  FLInternalSuggestionsContainer* processWord(FLWord* inputWord, FLString* rawText, FLWordList& hints);
  FLAddWordResult addWord(const FLString& word, float frequency);
  bool removeWord(const FLString& wordLetters);
  ////////////////////
  
  FLPoint keymaps[4][KEY_MAX_VALUE];
  
  int loadedWordCount();
  bool isWordInDictionary(const FLString& printLetters, bool allowLowerCase);
  FLWord* getWordByString(const FLString& s, bool allowLowerCase = false);
  FLWord* getRandomWord(int length);
  FLPoint* pointsFromLetters(const FLString& letters);
  FLString lettersFromPoints(FLPoint* points, short nPoints);
  FLPoint getPointForChar(FLChar c, int keyboard);
  float getDistanceBetweenLetters(FLChar c1, FLChar c2);
  
  
  FLWordDatabase* getWordDatabase();
  bool getLoadedPreprocessedFiles();
  bool getPostloaded();
  


};

#endif
