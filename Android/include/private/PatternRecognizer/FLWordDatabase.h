//
//  FLWordDatabase.h
//  PatternRecognizer
//
//  Created by Kostas Eleftheriou on 7/5/12.
//  Copyright (c) 2012 Syntellia Inc. All rights reserved.
//

#ifndef FLWORDDATABASE_H
#define FLWORDDATABASE_H

#include "CoreSettings.h"
#include "FLBlackBox.h"
#include "FLVotesHolder.h"
#include "FLInternalSuggestionsContainer.h"
#include "FLWord.h"
#include "FLString.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <string.h>

using namespace std;

#if SHAPE_TESTING
#define MIN_BASE_LENGTH 0.001
#else
#define MIN_BASE_LENGTH 50
#endif
#define REGION_SEARCH_LIMIT 1
#define USE_MIDPOINT 0

typedef uint16_t FLTokenID;

class FLWordDatabase {
private:
  
  bool FLEKSY_CORE_SETTING_SEARCH_MINUS_EXTRA;
  
  FLWordPtr wordsByID[FL_MAX_WORD_ID];
  FLBlackBox* blackboxesByLength[FLEKSY_MAX_WORD_SIZE+1]; //1-based index
  BBValue maxWordID;
  FLVotesHolder* votesHolder;

  FLWordPtrList wordsByLength[FLEKSY_MAX_WORD_SIZE+1]; //1-based index. Length 0 holds special non-words like "." and ","

  
  std::unordered_map<FLStringPtr, FLWordPtr, FLStringPtrHash, FLStringPtrEqual> wordsByLetters;
  std::unordered_map<FLStringPtr, FLStringPtr, FLStringPtrHash, FLStringPtrEqual> wordsBlacklistByLetters;

  
  //returns point of word with index bi, OR fixed points BASEPOINT_CUSTOM1_ID or BASEPOINT_CUSTOM2_ID
  static FLPoint getBasePointOfWord(const FLWord* word, int bi);
  //returns point of word with index pi in a coordinate system where basepoints b1 and b2 are stretched and moved to become (0,0) and (1,0)
  static FLPoint getBasisCoordsForWord(const FLWord* word, int pi, FLPoint b1, FLPoint b2, bool normalize = true);
  
  void createEmptyTables();
  
  // FLWordDatabase (QueryingMethods)
  void _voteWithParams1(VoteParameters params, VoteResult* result);
  void __voteWithParams2(VoteParameters params, VoteResult* result, BBKey key);
  void _voteWithParams2(VoteParameters params, VoteResult* result);
  void _voteWithParams(VoteParameters params, VoteResult* result);
  void voteWithParams(VoteParameters params, VoteResult* result);
  void paramsToBucketsAndVote(VoteResult result);
  void voteSingleBasisForInputWord(const FLWord* inputWord, int i, int bi1, int bi2, VoteResult* result);
  static float getBasisCoordDistanceForWordForPreciseScore(const FLWord* inputWord, const FLWord* word2, int pi, int bi1, int bi2);
  void vote(const FLWord* word, int bi1, int bi2, VoteResult* result);
  void vote(const FLWord* word, VoteResult* result);

  // FLWordDatabase (LoadingMethods)
  void modifyBlackboxValuesFor(FLWordPtr &word, int bi1, int bi2, bool addRemove);
  void modifyBlackboxValuesFor(FLWordPtr &word, bool addRemove);

  // FLWordDatabase (DebugMethods)
  static void _printResults(FLWordList* words, FLVotesHolder* votesHolder);
  static void printResults(FLInternalSuggestionsContainer* results, FLVotesHolder* votesHolder);
  void displayStats();
  
  static void printVoteParams(VoteParameters params);
  
  static int getStartIndex(int length, int bi1);

  std::unordered_map<FLTokenID, FLStringPtr> tokenIDToStringMap;

public:
  FLWordDatabase();
  ~FLWordDatabase();
  
  size_t allWordsCount = 0;

  // FLWordDatabase (QueryingMethods)
  FLInternalSuggestionsContainer* processWordInternal(const FLWord* inputword, bool needPreciseScore, bool printResults);
  static void calculatePreciseCandidateScore(FLWord* candidate, const FLWord* inputWord, bool force = true, float penalty = 1);
  
  static size_t firstPassResultsForLength(size_t length);
  
  // FLWordDatabase (LoadingMethods)
  //external only for now, will be private
  void loadedWord(FLWordPtr &word, bool calculateBlackboxValues);
  bool removeWord(FLWordPtr &word);
  void calculateBlackboxValues();
  bool preprocessedFilesExist(const string filepathFormat);
  void loadTablesWithPathFormat(const string filepathFormat);
  void loadTableWithContents(int wordLength, const void* contents, size_t length);
  void writeTables(const string filepath);
  BBValue generateWordID();
  
  void clearValues();
  
  FLWord *getWordByID(int wordID);
  FLWordPtr getWordPtrByID(int wordID);

  bool getTokenIDForFLString(FLStringPtr &string, FLTokenID *tokenIDRef);
  bool getFLStringForTokenID(FLTokenID tokenID, FLStringPtr &string);
  void addWordToTokenDatabase(FLStringPtr &wordString, BBValue uniqueID);

  //
  FLWordPtr getWordFromDictionary(FLStringPtr &key);
  void setWordInDictionary(FLStringPtr &key, FLWordPtr &word);
  //
  bool isWordInBlacklist(FLStringPtr &printLetters);
  void addWordToBlacklist(FLStringPtr &word);

  // these should be between 0.0 and 1.0
  // Platform is platform suggestions
  // Transform is transformation, unrelated to shape
  static float SHAPE_LAYER_WEIGHT;
  static float TRANSFORM_LAYER_WEIGHT;
  static float CONTEXT_LAYER_WEIGHT;
  static float PLATFORM_LAYER_WEIGHT;
  
  // Settings
  void setSettingPlusMinus1(bool b);
  bool getSettingPlusMinus1();
};

#endif

