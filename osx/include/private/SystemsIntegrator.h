//
//  SystemsIntegrator.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 7/30/11.
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#include <string>
#include <vector>
#include "FleksyUtilities.h"
#include "FLSocketsCommon.h"

// The following two #ifndefs are needed for iFleksy.
// These are nominally declared in `FLKeyTapsRecognizer.h`, but by including that header, it causes a huge dependency cascade when used from iFleksy.
// This is ugly, but IMHO, better than the alternative.  :(

#ifndef FLFOUNDWORDS_DEFINED
#define FLFOUNDWORDS_DEFINED
typedef struct {
  FLUnicodeString word;
  FLUnicodeString tapWord;
  double shapeScore;
  double contextScore;
  double score;
  bool isExtraWord;
} FLFoundWords;
#endif

#ifndef FLFOUNDWORDSVECTOR_DEFINED
#define FLFOUNDWORDSVECTOR_DEFINED
typedef std::vector<FLFoundWords> FLFoundWordsVector;
#endif

class FLTapsToWords;
typedef std::shared_ptr<FLTapsToWords> FLTapsToWordsPtr;

class FLRequest {
public:
  FLUnicodeString hint;
  FLUnicodeString previousToken1;
  FLUnicodeString previousToken2;
  std::vector<FLUnicodeString> platformSuggestions;
  bool debug;
  double requestTime;
  std::vector<FLPoint> points;
  //////////////////////////////////////////
  //~FLRequest();
  
  FLRequest(const std::vector<FLPoint> &_points, const FLUnicodeString &previousToken1, const FLUnicodeString &previousToken2, const FLUnicodeString hint, bool debug = false);
};

class SystemsIntegrator {
  
private:
  FLFoundWordsVector _foundWordsVector;
  bool blindMode = false;
  
public:
  SystemsIntegrator();
  ~SystemsIntegrator();

  FleksyUtilities* utils = NULL;
  //FLTokenPredictor* ftp = NULL;
  
  std::vector<FLUnicodeString> noChangeWords;
  
  //FLSpaceHelper* spaceHelper = NULL;
  
  FLTapsToWordsPtr tapsToWords;
  
  /**
   Gets the FLFoundWords associated with the last call to getCandidatesForRequest
   @param index of the word to get. Same ordering as the suggested words
   @returns a FLFoundWords object
   */
  FLFoundWords getFoundWord(size_t index);
  
  size_t numWordsFound();
  
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
