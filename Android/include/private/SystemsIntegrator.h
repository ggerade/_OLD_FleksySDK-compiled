//
//  SystemsIntegrator.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 7/30/11.
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

//#include <Foundation/Foundation.h>
//#include <UIKit/UITextChecker.h>

#include "FleksyUtilities.h"
#include "FLSocketsCommon.h"
#include "FLTokenPredictor.h"
#include <string>
#include <vector>

using namespace std;

class SystemsIntegrator {
  
private:
  FleksyUtilities* utils;
  
  FLTokenPredictor* ftp;

  token_ids convertToTokenIDs(FLString* token2, FLString* token1);
  float distanceBetweenLetters(FLChar c1, FLChar c2);
  float OptimalStringAlignmentDistance(const FLString* _str1, const FLString* _str2);
  FLWordList processContextResults(const list_pred& preds, int wordLength, int resultsLimit = 0);
  void ensureRawWordExists(FLInternalSuggestionsContainer* pwr, FLRequest* request);
  
public:
  SystemsIntegrator();
  ~SystemsIntegrator(); 
  
  void prepareContextResults(FLString* token1, FLString* token2);
  FLResponse* getCandidatesForRequest(FLRequest* request);
  
  void loadKeyboardData(void* data, size_t dataLength, bool isEncrypted);
  //void preloadWithPathFormat(const string& filepathFormat);
  // TODO: preprocessed file should include wordLength and length info
  void preloadWithContents(int wordLength, const void* contents, size_t contentLength);
  void loadDictionary(const string& tag, void* data, size_t dataLength, const FLString& delimiter, kWordlistType type, bool isEncrypted);
  
  void loadDictionary(FLFile& f, const FLString& delimiter, kWordlistType type, bool isEncrypted);
  
  void loadContextData(const string& unigram_file,
                       const string& bigram_file,
                       const string& trigram_file,
                       const string& unigram_hash,
                       const string& bigram_hash,
                       const string& trigram_hash,
                       bool alsoLoadInMemory);
  
  void writeTablesIfNeeded(const string& filepath);
  void postload();
  
  FLAddWordResult addUserWord(const FLString& word, float frequency);
  bool removeUserWord(const FLString& word);
  bool wordExists(const FLString& word, bool allowLowerCase);
  
  // caller needs to free pointer when done
  FLPoint* pointsFromLetters(const FLString& letters);
  FLPoint getPointForChar(FLChar c, int keyboard);
  
  FLWord* getWordByString(const FLString& s, bool allowLowerCase);
  
  // returns FLPoint[KEY_MAX_VALUE];
  FLPoint* getKeymap(int keyboardTag);
  
  // Settings
  void setSettingTransformLayerWeight(float weight);
  void setSettingShapeLayerWeight(float weight);
  void setSettingContextLayerWeight(float weight);
  void setSettingPlatformLayerWeight(float weight);
  
  bool getSettingShapeLayerWeight();
  bool getSettingTransformLayerWeight();
  bool getSettingContextLayerWeight();
  bool getSettingPlatformLayerWeight();
  
  
  bool getSettingPlusMinus1();
  void setSettingPlusMinus1(bool b);
  
  string getVersion();
};
