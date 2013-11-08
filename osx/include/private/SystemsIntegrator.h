//
//  SystemsIntegrator.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 7/30/11.
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

//#include <Foundation/Foundation.h>
//#include <UIKit/UITextChecker.h>

#include <string>
#include <vector>
#include "FleksyUtilities.h"
#include "FLSocketsCommon.h"
#include "FLSpaceHelper.h"
#include "FLTapsToWords.h"

class FLRequest {
public:
  FLUnicodeString previousToken1;
  FLUnicodeString previousToken2;
  std::vector<FLUnicodeString> platformSuggestions;
  bool debug;
  double requestTime;
  std::vector<FLPoint> points;
  //////////////////////////////////////////
  //~FLRequest();
  
  FLRequest(const std::vector<FLPoint> &_points, const FLUnicodeString &previousToken1, const FLUnicodeString &previousToken2, bool debug = false);
};

class SystemsIntegrator {
  
private:
  
  bool blindMode = false;
  
public:
  SystemsIntegrator();
  ~SystemsIntegrator();

  FleksyUtilities* utils = NULL;
  //FLTokenPredictor* ftp = NULL;
  
  std::vector<FLUnicodeString> noChangeWords;
  
  //FLSpaceHelper* spaceHelper = NULL;
  
  FLTapsToWordsPtr tapsToWords;
  
  std::vector<FLUnicodeString> getCandidatesForRequest(FLRequest &request);
  
  FLPoint loadKeyboardData(FLFilePtr &keyboardFile, bool isEncrypted);
  void loadDictionary(const std::string& tag, void* data, size_t dataLength, const FLUnicodeString& delimiter, kWordlistType type, bool isEncrypted);
  
  void loadDictionary(FLFilePtr &f, const FLUnicodeString& delimiter, kWordlistType type, bool isEncrypted);
  
  void postload();
  
  FLAddWordResult addUserWord(FLUnicodeStringPtr &word);
  bool removeUserWord(const FLUnicodeString& word);
  bool wordExists(const FLUnicodeString& word, bool allowLowerCase);
  
  void pointsFromLetters(const FLUnicodeString& letters, FLPoint points[]);
  FLPoint getPointForChar(FLUnicodeString c, FLKeyboardID keyboard);
    
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
  
  
  //bool getSettingPlusMinus1();
  //void setSettingPlusMinus1(bool b);
  
  FLUnicodeString getVersion();
};
