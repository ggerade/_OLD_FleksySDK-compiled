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
  float distanceBetweenLetters(FLChar c1, FLChar c2, FLKeyboardID keyboardID);
  float OptimalStringAlignmentDistance(const FLString* _str1, const FLString* _str2);
  FLWordList processContextResults(const list_pred& preds, int wordLength, int resultsLimit = 0);
  void ensureRawWordExists(FLInternalSuggestionsContainer* pwr, FLRequest* request);
  
public:
  SystemsIntegrator();
  ~SystemsIntegrator(); 
  
  void prepareContextResults(FLString* token1, FLString* token2);
  FLResponse* getCandidatesForRequest(FLRequest* request);
  
  FLPoint loadKeyboardData(FLFilePtr &keyboardFile, bool isEncrypted);
  //void preloadWithPathFormat(const string& filepathFormat);
  // TODO: preprocessed file should include wordLength and length info
  void preloadWithContents(int wordLength, const void* contents, size_t contentLength);
  void loadDictionary(const string& tag, void* data, size_t dataLength, const FLString& delimiter, kWordlistType type, bool isEncrypted);
  
  void loadDictionary(FLFilePtr &f, const FLString& delimiter, kWordlistType type, bool isEncrypted);
  
  void loadContextData(FLFilePtr &file1, FLFilePtr &file2, FLFilePtr &file3, bool alsoLoadInMemory);
  
  void writeTablesIfNeeded(const string& filepath);
  void postload();
  
  FLAddWordResult addUserWord(const FLString& word);
  bool removeUserWord(const FLString& word);
  bool wordExists(const FLString& word, bool allowLowerCase);
  
  // caller needs to free pointer when done
  FLPoint* pointsFromLetters(const FLString& letters);
  FLPoint getPointForChar(FLChar c, FLKeyboardID keyboard);
  
  FLWord* getWordByString(const FLString& s, bool allowLowerCase);
  
  FLKeyboardPtr& getKeyboard();

  // Settings
  void setSettingTransformLayerWeight(float weight);
  void setSettingShapeLayerWeight(float weight);
  void setSettingContextLayerWeight(float weight);
  void setSettingPlatformLayerWeight(float weight);
  
  float getSettingShapeLayerWeight();
  float getSettingTransformLayerWeight();
  float getSettingContextLayerWeight();
  float getSettingPlatformLayerWeight();
  
  
  bool getSettingPlusMinus1();
  void setSettingPlusMinus1(bool b);
  
  string getVersion();
};
