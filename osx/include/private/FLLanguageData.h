//
//  FLLanguageData.h
//  FleksySDK
//
//  Created by Dennis Horte on 7/18/14.
//  Copyright (c) 2014 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLLanguageData__
#define __FleksySDK__FLLanguageData__

#include "FLUnicodeString.h"
#include "FleksyDefines.h"

class FLLanguageData {
public:
  FLLanguageData();
  
  bool includeSymbolsInSuggestions() { return false; }
  
  void setTallCandies(bool tall) { _tallCandies = tall; }
  bool tallCandies() const { return _tallCandies; }
  
  void setRightToLeft(bool rtl) { _rightToLeft = rtl; }
  bool rightToLeft() const { return _rightToLeft; }
  
  void setUsesCaps(bool uses) { _usesCaps = uses; }
  bool usesCaps() { return _usesCaps; }
  
  void setLanguage(kLanguage l) { _language = l; }
  kLanguage getLanguage() const { return _language; }
  
  void setPunctuation(std::vector<FLUnicodeString> p) { _punctuation = p; }
  std::vector<FLUnicodeString> getPunctuation() const { return _punctuation; }
  
  void setFullStops(std::vector<FLUnicodeString> f) { _fullStops = f; }
  std::vector<FLUnicodeString> getFullStops() const { return _fullStops; }
  
private:
  bool _tallCandies = false;
  bool _rightToLeft = false;
  bool _usesCaps = true;
  kLanguage _language;
  
  std::vector<FLUnicodeString> _punctuation;
  std::vector<FLUnicodeString> _fullStops;
};

#endif /* defined(__FleksySDK__FLLanguageData__) */
