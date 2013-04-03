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
#include <vector>
#include <string>

using namespace std;

//these need to fit in 5 bits for now, so <= 31, and not conflict with ACTUAL base IDs that might be that large! TODO
#define BASEPOINT_CUSTOM1_ID 29
#define BASEPOINT_CUSTOM2_ID (BASEPOINT_CUSTOM1_ID + 1)

#define MIN_BASE_LENGTH 50

class FLWordDatabase {
private:
  
  bool FLEKSY_CORE_SETTING_USE_TX;
  bool FLEKSY_CORE_SETTING_SEARCH_MINUS_EXTRA;
  
  FLWord* wordsByID[FLEKSY_MAX_WORDS];
  FLBlackBox* blackboxesByLength[FLEKSY_MAX_WORD_SIZE+1]; //1-based index TODO switch to 0
  unsigned short maxWordID;
  FLVotesHolder* votesHolder;

  FLWordList wordsByLength[FLEKSY_MAX_WORD_SIZE+1]; //1-based index TODO switch to 0
  // TODO: move allWords, wordsByLetters, wordsBlacklistByLetters etc here or subclass.
  
  //returns point of word with index bi, OR fixed points BASEPOINT_CUSTOM1_ID or BASEPOINT_CUSTOM2_ID
  FLPoint getBasePointOfWord(FLWord* word, int bi);
  //returns point of word with index pi in a coordinate system where basepoints b1 and b2 are stretched and moved to become (0,0) and (1,0)
  FLPoint getBasisCoordsForWord(FLWord* word, int pi, FLPoint b1, FLPoint b2);
  
  void createEmptyTables();
  
  // FLWordDatabase (QueryingMethods)
  void _voteWithParams1(VoteParameters params, VoteResult* result);
  void __voteWithParams2(VoteParameters params, VoteResult* result, long long key);
  void _voteWithParams2(VoteParameters params, VoteResult* result);
  void _voteWithParams(VoteParameters params, VoteResult* result);
  void voteWithParams(VoteParameters params, VoteResult* result);
  void paramsToBucketsAndVote(VoteResult result);
  void voteSingleBasisForInputWord(FLWord* inputWord, int i, int bi1, int bi2, VoteResult* result);
  float getBasisCoordDistanceForWord(FLWord* word1, FLWord* word2, int pi, int bi1, int bi2);

  // FLWordDatabase (LoadingMethods)
  void modifyBlackboxValuesFor(FLWord* word, int bi1, int bi2, bool addRemove);
  void modifyBlackboxValuesFor(FLWord* word, bool addRemove);

  // FLWordDatabase (DebugMethods)
  static void _printResults(FLWordList* words, FLVotesHolder* votesHolder);
  static void printResults(FLInternalSuggestionsContainer* results, FLVotesHolder* votesHolder);
  void displayStats();


public:
  FLWordDatabase();
  ~FLWordDatabase();
  
  // FLWordDatabase (QueryingMethods)
  FLInternalSuggestionsContainer* processWordInternal(FLWord* inputword, FLString* rawText, int incrementalIndex, bool needscore, bool printResults);
  
  // FLWordDatabase (LoadingMethods)
  //external only for now, will be private
  void loadedWord(FLWord* word, bool calculateBlackboxValues);
  bool removeWord(FLWord* word);
  void calculateBlackboxValues();
  bool preprocessedFilesExist(const string filepathFormat);
  void loadTablesWithPathFormat(const string filepathFormat);
  void loadTableWithContents(int wordLength, const char* contents, size_t length);
  void writeTables(const string filepathFormat);
  unsigned short generateWordID();
  
  FLWord* getWordByID(int wordID);
  
  // Settings
  void setSettingUseTx(bool b);
  void setSettingPlusMinus1(bool b);
  //
  bool getSettingUseTx();
  bool getSettingPlusMinus1();
};

#endif

