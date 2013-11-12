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

struct FLPointComp {
  bool operator() (const FLPoint& lhs, const FLPoint& rhs) const { return((lhs.x < rhs.x) ? true : (lhs.x > rhs.x) ? false : (lhs.y < rhs.y) ? true : false); }
};
typedef std::map<FLPoint, std::vector<FLUnicodeString>, FLPointComp> FLPointToCharVectorMap;

class FLKeyboard {

private:
  typedef struct {
    uint16_t u16Character;
    FLPoint point;
  } FLUTF16Point;
  
  enum {
    FLUTF16ToPointsSize = 512
  };
  
  FLUTF16Point utf16ToPoints[FLUTF16ToPointsSize];
  
  FLKeyboardID activeKeyboardID;
  FLPoint keyboardSize;
  
  void loadKeyboardData(const FLFilePtr &keyboardFile, bool isEncrypted);
  FLUnicodeString getNearestLetterForPoint(FLPoint target);
  std::vector<FLPointToCharVectorMap> pointKeyMap;
  
  FLUnicodeStringToPointMap allKeysToPointMap;
  std::vector<FLUnicodeStringToPointMap> keysToPointMap;

  FLUnicodeStringToPointMap dawgAlphaKeyToPointMap;

public:
  FLKeyboard(const FLFilePtr &keyboardFile, bool isEncrypted);
  ~FLKeyboard();
  
  inline bool dawgGetPointForAlphaUTF16(uint16_t c, FLPoint &p) const {
    size_t hash = (0x920b5217UL ^ (0x811C9DC5 * c));
    for(size_t idx = 0; idx < FLUTF16ToPointsSize; idx++) {
      const FLUTF16Point *u16p = &utf16ToPoints[(hash + idx) % FLUTF16ToPointsSize];
      if(u16p->u16Character == c) { p = u16p->point; return(true); }
      if(u16p->u16Character == 0) { return(false); }
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
};

typedef std::shared_ptr<FLKeyboard> FLKeyboardPtr;

#endif /* defined(__FleksySDK__FLKeyboard__) */
