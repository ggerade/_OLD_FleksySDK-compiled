//
//  SystemsIntegrator.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 7/30/11.
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#ifndef __FleksySDK__FLSystemIntegrator__
#define __FleksySDK__FLSystemIntegrator__

#include <string>
#include <vector>
#include <array>
#include "FleksyUtilities.h"
#include "FLKeyTapRecognizer.h"
#include "FLLanguageData.h"

class FLTapsToWords;
typedef std::shared_ptr<FLTapsToWords> FLTapsToWordsPtr;

class FLRequest {
public:
  FLUnicodeString hint;
  FLUnicodeString previousToken1;
  FLUnicodeString previousToken2;
  std::vector<FLUnicodeString> platformSuggestions;
  std::vector<FLUnicodeString> pointlessChars; // Punctuation, numbers, etc.
  bool debug;
  double requestTime;
  std::vector<FLPoint> points;
  //////////////////////////////////////////
  //~FLRequest();
  
  FLRequest(const std::vector<FLPoint> &_points, const FLUnicodeString &previousToken1, const FLUnicodeString &previousToken2, const FLUnicodeString hint, bool debug = false);
};

class SystemsIntegrator {
private:
  FLLanguageData &_lang;
  bool blindMode = false;
  FLFoundWordsVector _foundWordsVector;
  FLUnicodeMap<bool>::Type _secondaryUserWords;
  
  std::shared_ptr<const FLDawg> _userDawg;
  
public:
  SystemsIntegrator(FLLanguageData &l);

  std::unique_ptr<FleksyUtilities> utils;
  std::vector<FLUnicodeString> noChangeWords;
  
  FLTapsToWordsPtr tapsToWords;
  
  inline const FLFoundWordsVector &getFoundWords() const {
    return _foundWordsVector;
  }
  
  void initSecondaryUserWords(FLFilePtr userFile);
  
  std::vector<FLUnicodeString> getCandidatesForRequest(FLRequest &request);
  
  void loadUserDawg();
  void loadKeyboardData(FLFilePtr &keyboardFile, FLFilePtr &commonFile);
  
  void postload();
  
  bool wordExists(const FLUnicodeString& word, bool allowLowerCase);
  
  void pointsFromLetters(const FLUnicodeString& letters, FLPoint points[]);
  FLPoint getPointForChar(FLUnicodeString c, FLKeyboardID keyboard);
    
  std::shared_ptr<FLKeyboard> getKeyboard();

  // Settings
  bool setSpaceBreaksEnabled(bool value); // returns new value. If return value does not match argument some error occurred
  bool getSpaceBreaksEnabled() const;
  bool setMissingTapsEnabled(bool value); // returns new value. If return value does not match argument some error occurred
  bool getMissingTapsEnabled() const;
  bool setTranspositionsEnabled(bool value);
  bool getTranspositionsEnabled() const;
  
  void setBlindMode(bool value);
  
  void setBayesianBlending(bool useBayesian);

  FLUnicodeString getVersion();
  
  /*
   Use this function whenever reading or writing the user dawg file in order to avoid access
   collisions in the case that the file system doesn't handle this correctly.
   */
  static void withUserDawgReadWriteMutex(std::function<void()> f);
  
};

#endif
