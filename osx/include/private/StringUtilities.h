//
//  StringUtilities.h
//  FleksyLib
//
//  Created by Kosta Eleftheriou on 4/17/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksyLib__StringUtilities__
#define __FleksyLib__StringUtilities__

#include <iostream>
#include "FLString.h"

#define USE_TABLES_BY_DEFAULT 1

class StringUtilities {
  
public:

  static bool postprocessed;
  
  static FLChar toupper_table[256];
  static FLChar tolower_table[256];
  static bool ismember_table[3][256];
  
  static FLString alphabetFull;
  static FLString alphabetUpper;
  static FLString alphabetLower;
  
  static FLChar toupper(FLChar c, bool table = USE_TABLES_BY_DEFAULT);
  static FLChar tolower(FLChar c, bool table = USE_TABLES_BY_DEFAULT);
  static bool isalpha(FLChar c, bool table = USE_TABLES_BY_DEFAULT);
  static bool isupper(FLChar c, bool table = USE_TABLES_BY_DEFAULT);
  static bool islower(FLChar c, bool table = USE_TABLES_BY_DEFAULT);
  
  static bool ismember(FLChar item, FLString& vector, bool table = USE_TABLES_BY_DEFAULT);
  
  static FLString onlyKeepAlphaFromString(const FLString& s);
  
  // This converts extended ascii based on the ISO-8859-1 (Latin1) character set into UTF8 multibyte characters (up to 2 multibytes)
  static char* extendedAsciiToUtf8(const char* text);
  
  static void makeLowerCase(FLString* s);
  
  static void postprocess();
  
  static void cleanup();
  
};

#endif /* defined(__FleksyLib__StringUtilities__) */
