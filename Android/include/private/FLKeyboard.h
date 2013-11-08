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

class FLKeyMap{
public:
  void set(const FLUnicodeString &c, FLPoint point);
  FLPoint get(const FLUnicodeString &c);
  FLUnicodeString getNearestChar(FLPoint point);
  std::map<FLUnicodeString, FLPoint> getKeyMap();
  
private:
  FLUnicodeStringToPointMap keys;
};

struct FLPointComp {
  bool operator() (const FLPoint& lhs, const FLPoint& rhs) const { return((lhs.x < rhs.x) ? true : (lhs.x > rhs.x) ? false : (lhs.y < rhs.y) ? true : false); }
};
typedef std::map<FLPoint, std::vector<FLUnicodeString>, FLPointComp> FLPointToCharVectorMap;


class FLKeyboard {

private:
  FLKeyMap keymaps[FLKeyboardID_NUMBER_OF_KEYBOARDS];
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

  std::map<FLUnicodeString, FLPoint> getKeymapForKeyboard(FLKeyboardID keyboardID);
};

typedef std::shared_ptr<FLKeyboard> FLKeyboardPtr;

#endif /* defined(__FleksySDK__FLKeyboard__) */
