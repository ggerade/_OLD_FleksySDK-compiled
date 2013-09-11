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
#include "FLSpaceHelper.h"
#include <string>
#include <vector>

#ifdef FL_USE_DAWG_SVD_ENGINE
#include "FLKeyTapRecognizer.h"
#endif

using namespace std;

class SystemsIntegrator {
  
private:
  
  bool blindMode = false;
  word_id getTokenID(FLString* token);
  float distanceBetweenLetters(FLChar c1, FLChar c2, FLKeyboardID keyboardID);
  float OptimalStringAlignmentDistance(const FLString* _str1, const FLString* _str2);
  void ensureRawWordExists(FLInternalSuggestionsContainer* pwr, FLRequest* request, const FLWord* inputWord);
  
public:
  SystemsIntegrator();
  ~SystemsIntegrator();

  FleksyUtilities* utils = NULL;
  FLTokenPredictor* ftp = NULL;
  
  vector<FLString*> noChangeWords;
  
  FLSpaceHelper* spaceHelper = NULL;
  
  FLWordList processContextResults(const list_pred& preds, int wordLength, int resultsLimit = 0);
  token_ids convertToTokenIDs(FLString* token2, FLString* token1);

#ifdef FL_USE_DAWG_SVD_ENGINE
  FLKeyTapRecognizerPtr keyTapRecognizer;
#endif
  
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
  
  FLAddWordResult addUserWord(FLStringPtr &word);
  bool removeUserWord(const FLString& word);
  bool wordExists(const FLString& word, bool allowLowerCase);
  
  void pointsFromLetters(const FLString& letters, FLPoint points[]);
  FLPoint getPointForChar(FLChar c, FLKeyboardID keyboard);
  
  FLWordPtr getWordByString(const FLString& s, bool allowLowerCase);
  
  FLKeyboardPtr& getKeyboard();

  // Settings
  bool setSpaceBreaksEnabled(bool value); // returns new value. If return value does not match argument some error occurred
  bool getSpaceBreaksEnabled();
  void setBlindMode(bool value);
  
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
