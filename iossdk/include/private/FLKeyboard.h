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

enum {
  FLUTF32PointMaxPoints = 3
};

typedef struct {
  uint32_t u32Character;
  uint8_t numPoints;
  FLPoint points[FLUTF32PointMaxPoints];
} FLUTF32Point;

class FLKeyboard {

private:

  enum {
    FLUTF32ToPointsSize = 512
  };
  
  static const std::vector<FLUnicodeString> allAccentData;
  
  FLUTF32Point utf32ToPoints[FLUTF32ToPointsSize];
  
  FLKeyboardID activeKeyboardID;
  FLPoint keyboardSize;
  
  FLUnicodeString getNearestLetterForPoint(FLPoint target);
  std::vector<FLPointToCharVectorMap> pointKeyMap;
  
  FLUnicodeStringToPointMap allKeysToPointMap;
  std::vector<FLUnicodeStringToPointMap> keysToPointMap;

  std::unordered_map<FLUnicodeString, FLUTF32Point, FLUnicodeStringHash, FLUnicodeStringEqual> dawgAlphaKeyToPointMap;
//  FLUnicodeStringToPointMap dawgAlphaKeyToPointMap;
  
  
  void initializeFromLegacyData();
  void initializeFromModernData();
  void initializeModernKeyboard(size_t id);
  void initializeModernAccents();
  
  std::vector<std::vector<FLUnicodeString>> _keyboardLineData;
  std::vector<FLUnicodeString> _accentLineData;
  std::vector<FLUnicodeString> _legacyLineData;
  
  bool _useAllAccents = false;
  bool _useLegacyKeyboard = false;
  size_t _numShiftKeyboards = 0;

public:
  FLKeyboard();
  
  /*
   * Initialization methods
   *
   * Use these methods to set up the keyboard, and then call initialize, which will use the
   * prepared data and settings to set up the keyboard. This is done in place, so any existing
   * pointers to this keyboard will not be damaged.
   */
  void setDataFromFile(const FLFilePtr &keyboardFile);
  void setDataFromString(const FLUnicodeString &data);
  void setDataFromVector(const std::vector<FLUnicodeString> &lines);
  void setLegacyDataFromFile(const FLFilePtr &keyboardFile);
  void setUseAllAccents(bool useAll) { _useAllAccents = useAll; }
  void setUseLegacyKeyboard(bool legacy) { _useLegacyKeyboard = legacy; }
  
  /*
   * Call this before calling the setData functions.
   * If called afterwards, the data from those functions will be reset for keyboard ids
   * with default values.
   */
  void reset();
  
  /*
   * Call after setting the data using the setData family of functions to initialize
   * the internal representations based on the data.
   */
  void initialize();
  
  bool getUseAllAccents() const { return _useAllAccents; }
  
  size_t numShiftKeyboards() const { return _numShiftKeyboards; }
  
  inline const FLUTF32Point * dawgGetPointForAlphaUTF32(uint32_t c) const {
    size_t hash = (c == 0) ? 1 : c; // Required for proper operation of the LFSR.
    for(size_t idx = 0; idx < FLUTF32ToPointsSize; idx++) {
      const FLUTF32Point *u32p = &utf32ToPoints[(hash) % FLUTF32ToPointsSize];
      if(u32p->u32Character == c) { return u32p; }
      if(u32p->u32Character == 0) { return nullptr; }
      hash = ((hash >> 1) ^ ((0UL - (hash & 1UL)) & 0x80200003UL)); // 32-bit LFSR w/ 2^32 period.
    }
    return nullptr;
  }

  /*
   Get the points on the keyboard that match the passed character.
   
   @param c
   The character too look up points for. This should be a single grapheme, although it
   may have multiple code points.
   
   @returns
   nullptr if c does not appear on ont of the QWERTY layouts for this keyboard.
   The FLUTF32Point details otherwise. The FLUTF32Point.u32Character will be set to zero,
   since this function is doing the lookup via FLUnicodeString rather than UTF-32 code points.
   */
  const FLUTF32Point * dawgGetPointForAlphaChar(const FLUnicodeString &c) const;
  
  bool areAllCharactersOnQWERTYKeyboard(const FLUnicodeString &word) const;

  std::vector<FLUnicodeString> getNearestKeysForPoint(FLPoint point, FLKeyboardID keyboardID);
  FLUnicodeString getNearestPrimaryKeyForPoint(FLPoint point, FLKeyboardID keyboardID);

  FLPoint getKeyboardSize() const;

  void setPointForChar(FLPoint point, const FLUnicodeString &c, FLKeyboardID keyboardID);
  
  FLPoint getPointForChar(const FLUnicodeString &c, FLKeyboardID keyboardID);

  FLKeyboardID getCurrentKeyboardID() const;
  void setCurrentKeyboardID(FLKeyboardID keyboardID);
  bool isValidKeyboardID(FLKeyboardID kb) const;
  
  FLUnicodeString getNearestChar(FLPoint target);
  FLPoint getPointForChar(const FLUnicodeString &c);

  float getDistanceBetweenLetters(const FLUnicodeString &c1, const FLUnicodeString &c2);

  FLUnicodeString lettersFromPoints(const FLPoint points[], size_t nPoints);
  void pointsFromLetters(const FLUnicodeString &letters, FLPoint points[]);

  std::map<FLUnicodeString, FLPoint> getKeymapForKeyboard(FLKeyboardID keyboardID, bool includeAccents = false);
  FLPointToCharVectorMap getPointToCharVectorMapForKeyboard(FLKeyboardID keyboardID);
};

#endif /* defined(__FleksySDK__FLKeyboard__) */
