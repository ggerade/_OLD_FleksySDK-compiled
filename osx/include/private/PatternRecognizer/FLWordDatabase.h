//
//  FLWordDatabase.h
//  PatternRecognizer
//
//  Created by Kostas Eleftheriou on 7/5/12.
//  Copyright (c) 2012 Syntellia Inc. All rights reserved.
//

#ifndef FLWORDDATABASE_H
#define FLWORDDATABASE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <string.h>
#include <pthread.h>
#include "FLWord.h"
#include "FLUnicodeString.h"
#include "Platform.h"

class FLWordDatabase {
private:
  
  bool FLEKSY_CORE_SETTING_SEARCH_MINUS_EXTRA;
  
  std::unordered_map<size_t, FLWordPtrList> systemWordsByLength;
  std::unordered_map<size_t, FLWordPtrList> userWordsByLength;
  
  std::unordered_map<FLUnicodeStringPtr, FLWordPtr,          FLUnicodeStringPtrHash, FLUnicodeStringPtrEqual> wordsByLetters;
  std::unordered_map<FLUnicodeStringPtr, FLUnicodeStringPtr, FLUnicodeStringPtrHash, FLUnicodeStringPtrEqual> wordsBlacklistByLetters;
  
  pthread_mutex_t _recursiveMutex = PTHREAD_MUTEX_INITIALIZER;

public:
  FLWordDatabase();
  ~FLWordDatabase();
  
  void lock()    { pthread_mutex_lock(&_recursiveMutex); }
  bool tryLock() { return((pthread_mutex_trylock(&_recursiveMutex) == 0) ? true : false); }
  void unlock()  { pthread_mutex_unlock(&_recursiveMutex); }
  
  size_t allWordsCount = 0;
  
  // FLWordDatabase (LoadingMethods)
  //external only for now, will be private
  void loadedWord(FLWordPtr &word, bool userWord);
  bool removeWord(FLWordPtr &word);
  
  FLWordPtrList getUserWordsForLength(size_t length);

  //
  FLWordPtr getWordFromDictionary(FLUnicodeStringPtr &key);
  void setWordInDictionary(FLUnicodeStringPtr &key, FLWordPtr &word);
  //
  bool isWordInBlacklist(FLUnicodeStringPtr &printLetters);
  void addWordToBlacklist(FLUnicodeStringPtr &word);

  // these should be between 0.0 and 1.0
  // Platform is platform suggestions
  // Transform is transformation, unrelated to shape
  static float SHAPE_LAYER_WEIGHT;
  static float TRANSFORM_LAYER_WEIGHT;
  static float CONTEXT_LAYER_WEIGHT;
  static float PLATFORM_LAYER_WEIGHT;
};

#endif
