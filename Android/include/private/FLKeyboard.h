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

#include "FLFile.h"
#include "FLKeyMap.h"
#include "FLEnums.h"

#define USE_TABLES_BY_DEFAULT 1

class FLKeyboard {

private:
  FLKeyMap keymaps[FLKeyboardID_NUMBER_OF_KEYBOARDS];
  FLKeyboardID activeKeyboardID;
  FLPoint keyboardSize;
  
  void loadKeyboardData(FLFilePtr &keyboardFile, bool isEncrypted);
  FLChar getNearestLetterForPoint(FLPoint& target);

  FLChar toupper_table[256];
  FLChar tolower_table[256];
  bool ismember_table[3][256];

  FLString alphabetFull;
  FLString alphabetUpper;
  FLString alphabetLower;

  bool ismember(FLChar item, FLString& vector, bool table = USE_TABLES_BY_DEFAULT);

public:
  FLKeyboard(FLFilePtr &keyboardFile, bool isEncrypted);
  ~FLKeyboard();
  
  FLPoint getKeyboardSize();

  void setPointForChar(FLPoint point, FLChar c, FLKeyboardID keyboardID);
  
  FLPoint getPointForChar(FLChar c, FLKeyboardID keyboardID);
  FLChar getNearestChar(FLPoint target, FLKeyboardID keyboardID);

  FLKeyboardID getCurrentKeyboardID();
  void setCurrentKeyboardID(FLKeyboardID keyboardID);
  
  FLChar getNearestChar(FLPoint target);
  FLPoint getPointForChar(FLChar c);

  float getDistanceBetweenLetters(FLChar c1, FLChar c2);

  FLString lettersFromPoints(FLPoint* points, short nPoints);
  void pointsFromLetters(FLStringPtr &letters, FLPoint points[]);

  FLChar toupper(FLChar c, bool table = USE_TABLES_BY_DEFAULT);
  FLChar tolower(FLChar c, bool table = USE_TABLES_BY_DEFAULT);
  bool isalpha(FLChar c, bool table = USE_TABLES_BY_DEFAULT);
  bool isupper(FLChar c, bool table = USE_TABLES_BY_DEFAULT);
  bool islower(FLChar c, bool table = USE_TABLES_BY_DEFAULT);

  FLStringPtr onlyKeepAlphaFromString(FLStringPtr &s);

  // This converts extended ascii based on the ISO-8859-1 (Latin1) character set into UTF8 multibyte characters (up to 2 multibytes)
  char* extendedAsciiToUtf8(const char* text);

  void makeLowerCase(FLStringPtr &s);
};

typedef std::shared_ptr<FLKeyboard> FLKeyboardPtr;

#endif /* defined(__FleksySDK__FLKeyboard__) */
