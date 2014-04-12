//
//  FLKeyboard.h
//  FleksySDK
//
//  Created by Kosta Eleftheriou on 5/13/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLKeyboard__
#define __FleksySDK__FLKeyboard__

#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <set>

#include "FLFile.h"
#include "FLEnums.h"
#include "FLUnicodeString.h"
#include "FLPoint.h"


class FLKeyboard {

private:
  typedef struct {
    uint32_t u32Character;
    FLPoint point;
  } FLUTF32Point;

  enum {
    FLUTF32ToPointsSize = 512
  };
  
  FLUTF32Point utf32ToPoints[FLUTF32ToPointsSize];
  
  FLKeyboardID activeKeyboardID;
  FLPoint keyboardSize;
  
  void loadKeyboardData(const FLFilePtr &keyboardFile, const FLFilePtr &commonData);
  void loadLegacyKeyboardData(const FLFilePtr &keyboardFile);
  FLUnicodeString getNearestLetterForPoint(FLPoint target);
  std::vector<FLPointToCharVectorMap> pointKeyMap;
  
  FLUnicodeStringToPointMap allKeysToPointMap;
  std::vector<FLUnicodeStringToPointMap> keysToPointMap;

  FLUnicodeStringToPointMap dawgAlphaKeyToPointMap;

public:
  FLKeyboard(const FLFilePtr &keyboardFile, const FLFilePtr &commonData);
  ~FLKeyboard();
  
  inline bool dawgGetPointForAlphaUTF32(uint32_t c, FLPoint &p) const {
    size_t hash = (0x920b5217UL ^ (0x811C9DC5 * c));
    for(size_t idx = 0; idx < FLUTF32ToPointsSize; idx++) {
      const FLUTF32Point *u32p = &utf32ToPoints[(hash + idx) % FLUTF32ToPointsSize];
      if(u32p->u32Character == c) { p = u32p->point; return(true); }
      if(u32p->u32Character == 0) { return(false); }
    }
    return(false);
  }

  bool dawgGetPointForAlphaChar(const FLUnicodeString &c, FLPoint &p) const {
    const FLUnicodeStringToPointMap::const_iterator &it = dawgAlphaKeyToPointMap.find(c);
    if(it == dawgAlphaKeyToPointMap.end()) { return(false); } else { p = it->second; return(true); }
  }

  std::vector<FLUnicodeString> getNearestKeysForPoint(FLPoint point, FLKeyboardID keyboardID);
  FLUnicodeString getNearestPrimaryKeyForPoint(FLPoint point, FLKeyboardID keyboardID);

  FLPoint getKeyboardSize();

  void setPointForChar(FLPoint point, const FLUnicodeString &c, FLKeyboardID keyboardID);
  
  FLPoint getPointForChar(const FLUnicodeString &c, FLKeyboardID keyboardID);

  FLKeyboardID getCurrentKeyboardID();
  void setCurrentKeyboardID(FLKeyboardID keyboardID);
  
  FLUnicodeString getNearestChar(FLPoint target);
  FLPoint getPointForChar(const FLUnicodeString &c);

  float getDistanceBetweenLetters(const FLUnicodeString &c1, const FLUnicodeString &c2);

  FLUnicodeString lettersFromPoints(const FLPoint points[], size_t nPoints);
  void pointsFromLetters(const FLUnicodeStringPtr &letters, FLPoint points[]);

  std::map<FLUnicodeString, FLPoint> getKeymapForKeyboard(FLKeyboardID keyboardID, bool includeAccents = false);
  FLPointToCharVectorMap getPointToCharVectorMapForKeyboard(FLKeyboardID keyboardID);
};

typedef std::shared_ptr<FLKeyboard> FLKeyboardPtr;

#endif /* defined(__FleksySDK__FLKeyboard__) */
