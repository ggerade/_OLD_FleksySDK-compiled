//
//  FLString.h
//  FleksySDK
//
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK_FLString_h__
#define __FleksySDK_FLString_h__

#define FLEKSY_USE_WIDE_CHARS 0

#include <iostream>
#if FLEKSY_USE_WIDE_CHARS
#include <wchar.h>
typedef std::wstring FLString;
typedef wchar_t FLChar;
#define NSStringToFLString _NSStringToStringW
#define FLStringToNSString _StringWToNSString
#define flcout std::wcout
#define flsprintf swprintf
#define FLTokenizer(__t__, __d__, __z__) wcstok(__t__, __d__, &__z__)
#define TEXT(s) L ## s
#define flatoi(s) atoi(string(s.begin(), s.end()).c_str())
#define flatof(s) atof(string(s.begin(), s.end()).c_str())
#define flstrtod(s) strtod(string(s.begin(), s.end()).c_str(), NULL)
#define flstrtof(s) strtof(string(s.begin(), s.end()).c_str(), NULL)
#else
#include <string>
typedef unsigned char FLChar;
typedef std::basic_string <FLChar> FLString;
#define NSStringToFLString _NSStringToString
#define FLStringToNSString _StringToNSString
#define flcout std::cout
#define flsprintf sprintf
#define FLTokenizer(__t__, __d__, __z__) (FLChar*) strtok((char*)__t__, __d__)
#define TEXT(s) FLString((char*)s).c_str()
#define FLStringMake(s) FLString((FLChar*) s)
//#define FLString(s) FLString((char*)s)
#define flatoi(s) atoi(string(s.begin(), s.end()).c_str())
#define flatof(s) atof(string(s.begin(), s.end()).c_str())
#define flstrtod(s) strtod(string(s.begin(), s.end()).c_str(), NULL)
#define flstrtof(s) strtof(string(s.begin(), s.end()).c_str(), NULL)
#endif

#define NSStringToString _NSStringToStringUTF8

#endif /* defined(__FleksySDK_FLString_h__) */
