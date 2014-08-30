//
//  FLUnicodeString.h
//  FleksySDK
//
//  Created by John Engelhart on 10/16/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//



// It's UN̎ͪ̒͑͏̜͓̲̥̹͙͖̝̟̘̦͇̺̮́I̷̡̜̗̰͙̲̱͖̳̰̰̖͍̙̻̞̍̂̐͂͐̅͡C̛͔̳̦̫̬̩̣̭̝ͫ͆̈́̿̌ͥ̉͂̑̍ͧ̽͊͟O̠̩̤̞̭͎͖̯̘̳͉̪̫̰͙̰͖̼ͥ̊͐̒͐͗̏̉̀ĎE, bitches!





#ifndef __FleksySDK__FLUnicodeString__
#define __FleksySDK__FLUnicodeString__

#include <stdint.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include "FLPoint.h"
#include "FLException.h"

#ifndef FLUNICODECODEPOINT_DEFINED
#define FLUNICODECODEPOINT_DEFINED
typedef uint32_t FLUnicodeCodePoint;
#endif

#define FLUnicodeStringWithUTF8(s) FLUnicodeString((const unsigned char *)s)

/*
 * API access for C/POSIX character classes is as follows:
 * - alpha:     u_isUAlphabetic(c) or u_hasBinaryProperty(c, UCHAR_ALPHABETIC)
 * - lower:     u_isULowercase(c) or u_hasBinaryProperty(c, UCHAR_LOWERCASE)
 * - upper:     u_isUUppercase(c) or u_hasBinaryProperty(c, UCHAR_UPPERCASE)
 * - punct:     u_ispunct(c)
 * - digit:     u_isdigit(c) or u_charType(c)==U_DECIMAL_DIGIT_NUMBER
 * - xdigit:    u_isxdigit(c) or u_hasBinaryProperty(c, UCHAR_POSIX_XDIGIT)
 * - alnum:     u_hasBinaryProperty(c, UCHAR_POSIX_ALNUM)
 * - space:     u_isUWhiteSpace(c) or u_hasBinaryProperty(c, UCHAR_WHITE_SPACE)
 * - blank:     u_isblank(c) or u_hasBinaryProperty(c, UCHAR_POSIX_BLANK)
 * - cntrl:     u_charType(c)==U_CONTROL_CHAR
 * - graph:     u_hasBinaryProperty(c, UCHAR_POSIX_GRAPH)
 * - print:     u_hasBinaryProperty(c, UCHAR_POSIX_PRINT)
 */

typedef enum FLUnicodeCategory {
  FL_UNASSIGNED              = 0,
  FL_GENERAL_OTHER_TYPES     = 0,
  FL_UPPERCASE_LETTER        = 1,
  FL_LOWERCASE_LETTER        = 2,
  FL_TITLECASE_LETTER        = 3,
  FL_MODIFIER_LETTER         = 4,
  FL_OTHER_LETTER            = 5,
  FL_NON_SPACING_MARK        = 6,
  FL_ENCLOSING_MARK          = 7,
  FL_COMBINING_SPACING_MARK  = 8,
  FL_DECIMAL_DIGIT_NUMBER    = 9,
  FL_LETTER_NUMBER           = 10,
  FL_OTHER_NUMBER            = 11,
  FL_SPACE_SEPARATOR         = 12,
  FL_LINE_SEPARATOR          = 13,
  FL_PARAGRAPH_SEPARATOR     = 14,
  FL_CONTROL_CHAR            = 15,
  FL_FORMAT_CHAR             = 16,
  FL_PRIVATE_USE_CHAR        = 17,
  FL_SURROGATE               = 18,
  FL_DASH_PUNCTUATION        = 19,
  FL_START_PUNCTUATION       = 20,
  FL_END_PUNCTUATION         = 21,
  FL_CONNECTOR_PUNCTUATION   = 22,
  FL_OTHER_PUNCTUATION       = 23,
  FL_MATH_SYMBOL             = 24,
  FL_CURRENCY_SYMBOL         = 25,
  FL_MODIFIER_SYMBOL         = 26,
  FL_OTHER_SYMBOL            = 27,
  FL_INITIAL_PUNCTUATION     = 28,
  FL_FINAL_PUNCTUATION       = 29,
  FL_CHAR_CATEGORY_COUNT
} FLUnicodeCategory;

namespace Fleksy {
  class EXPORT UnicodeConversionError : public Fleksy::Exception {
  public:
    explicit UnicodeConversionError(std::string message, std::string filename = "", int lineNumber = 0) {
      init(message, filename, lineNumber);
    }
  };
}

class FLUnicodeString : public std::basic_string<uint16_t> {
private:
  mutable std::string _utf8String;
  
public:
  FLUnicodeString();
  
  FLUnicodeString(const char utf8String[]);
  FLUnicodeString(const unsigned char *utf8String);
  FLUnicodeString(const unsigned char *utf8String, size_t utf8Length);
  FLUnicodeString(const std::string utf8String);
  FLUnicodeString(const uint16_t *utf16String, size_t utf16Length) { this->assign(utf16String, utf16Length); }

  bool containsOnlyISO8859Characters() const {
    size_t length = this->length();
    const uint16_t *p = this->data();
    bool onlyISO8859 = true;
    
    for(size_t idx = 0; idx < length; idx++) { if((*p) > 255) { onlyISO8859 = false; break; } p++; }
    return(onlyISO8859);
  }

  static bool containsOnlyTrivialCharacters(const uint16_t *buffer, size_t length) {
    bool onlyTrivial = true;
    
    for(size_t idx = 0; idx < length; idx++) {
      uint16_t codePoint = buffer[idx];
      if(codePoint > 255) {
        if( ! ((codePoint == 0x03b5) || (codePoint == 0x03ad) || (codePoint == 0x03c1) || (codePoint == 0x03c4) || (codePoint == 0x03c5) || (codePoint == 0x03cd) || (codePoint == 0x03cb) || (codePoint == 0x03b0) || (codePoint == 0x03b8) || (codePoint == 0x03b9) || (codePoint == 0x03af) || (codePoint == 0x03ca) || (codePoint == 0x0390) || (codePoint == 0x03bf) || (codePoint == 0x03cc) || (codePoint == 0x03c0) || (codePoint == 0x03b1) || (codePoint == 0x03ac) || (codePoint == 0x03c3) || (codePoint == 0x03c2) || (codePoint == 0x03b4) || (codePoint == 0x03c6) || (codePoint == 0x03b3) || (codePoint == 0x03b7) || (codePoint == 0x03ae) || (codePoint == 0x03be) || (codePoint == 0x03ba) || (codePoint == 0x03bb) || (codePoint == 0x03b6) || (codePoint == 0x03c7) || (codePoint == 0x03c8) || (codePoint == 0x03c9) || (codePoint == 0x03ce) || (codePoint == 0x03b2) || (codePoint == 0x03bd) || (codePoint == 0x03bc) || (codePoint == 0x0395) || (codePoint == 0x0388) || (codePoint == 0x03a1) || (codePoint == 0x03a4) || (codePoint == 0x03a5) || (codePoint == 0x038e) || (codePoint == 0x03ab) || (codePoint == 0x03a5) || (codePoint == 0x0308) || (codePoint == 0x0301) || (codePoint == 0x0398) || (codePoint == 0x0399) || (codePoint == 0x038a) || (codePoint == 0x03aa) || (codePoint == 0x0399) || (codePoint == 0x0308) || (codePoint == 0x0301) || (codePoint == 0x039f) || (codePoint == 0x038c) || (codePoint == 0x03a0) || (codePoint == 0x0391) || (codePoint == 0x0386) || (codePoint == 0x03a3) || (codePoint == 0x0394) || (codePoint == 0x03a6) || (codePoint == 0x0393) || (codePoint == 0x0397) || (codePoint == 0x0389) || (codePoint == 0x039e) || (codePoint == 0x039a) || (codePoint == 0x039b) || (codePoint == 0x0396) || (codePoint == 0x03a7) || (codePoint == 0x03a8) || (codePoint == 0x03a9) || (codePoint == 0x038f) || (codePoint == 0x0392) || (codePoint == 0x039d) || (codePoint == 0x039c) || (codePoint == 0x0401) || (codePoint == 0x0404) || (codePoint == 0x0406) || (codePoint == 0x0410) || (codePoint == 0x0411) || (codePoint == 0x0412) || (codePoint == 0x0413) || (codePoint == 0x0414) || (codePoint == 0x0415) || (codePoint == 0x0416) || (codePoint == 0x0417) || (codePoint == 0x0418) || (codePoint == 0x0419) || (codePoint == 0x041a) || (codePoint == 0x041b) || (codePoint == 0x041c) || (codePoint == 0x041d) || (codePoint == 0x041e) || (codePoint == 0x041f) || (codePoint == 0x0420) || (codePoint == 0x0421) || (codePoint == 0x0422) || (codePoint == 0x0423) || (codePoint == 0x0424) || (codePoint == 0x0425) || (codePoint == 0x0426) || (codePoint == 0x0427) || (codePoint == 0x0428) || (codePoint == 0x0429) || (codePoint == 0x042a) || (codePoint == 0x042b) || (codePoint == 0x042c) || (codePoint == 0x042d) || (codePoint == 0x042e) || (codePoint == 0x042f) || (codePoint == 0x0430) || (codePoint == 0x0431) || (codePoint == 0x0432) || (codePoint == 0x0433) || (codePoint == 0x0434) || (codePoint == 0x0435) || (codePoint == 0x0436) || (codePoint == 0x0437) || (codePoint == 0x0438) || (codePoint == 0x0439) || (codePoint == 0x043a) || (codePoint == 0x043b) || (codePoint == 0x043c) || (codePoint == 0x043d) || (codePoint == 0x043e) || (codePoint == 0x043f) || (codePoint == 0x0440) || (codePoint == 0x0441) || (codePoint == 0x0442) || (codePoint == 0x0443) || (codePoint == 0x0444) || (codePoint == 0x0445) || (codePoint == 0x0446) || (codePoint == 0x0447) || (codePoint == 0x0448) || (codePoint == 0x0449) || (codePoint == 0x044a) || (codePoint == 0x044b) || (codePoint == 0x044c) || (codePoint == 0x044d) || (codePoint == 0x044e) || (codePoint == 0x044f) || (codePoint == 0x0451) || (codePoint == 0x0454) || (codePoint == 0x0456))) {
          onlyTrivial = false;
          break;
        }
      }
    }
    return(onlyTrivial);
  }

  bool containsOnlyTrivialCharacters() const {
    return(containsOnlyTrivialCharacters(this->data(), this->length()));
  }
  
  const char *c_str() const {
    std::string tmpUTF8String = this->utf8String();
    if(_utf8String != tmpUTF8String) { _utf8String = tmpUTF8String; }
    return(_utf8String.c_str());
  }
  std::string utf8String() const;
  std::string iso8859String() const;
  std::string hexString() const;
  
  void setToUTF8String(const unsigned char *utf8String);
  void setToUTF8String(const unsigned char *utf8String, size_t length);
  void setToISO8859String(const unsigned char *iso8859String);
  void setToISO8859String(const unsigned char *iso8859String, size_t iso8859Length);

  int graphemeIndexFor(int index) const; // TODO - johne - refactor / rename

  int lengthOfNextGraphemeAt(int index) const;
  int lengthOfPreviousGraphemeAt(int index) const;
  FLUnicodeString graphemeAtIndex(int index) const;
  FLUnicodeString graphemeAtIndex(size_t index) const { return graphemeAtIndex((int) index); }
  
  // Similar to length, but returns number of graphemes, rather than number of code points.
  int gLength() const;
  
  // Similar to the operater[], but returns graphemes rather than single code points.
  // If some grapheme has more than one code point, this will still consider that grapheme to occupy a single position.
  // example: code points:     A B C D E
  //                           - --- - -
  //          display chars:   A  F  D E
  //   Then gCharAt(0) = FLUnicodeString("A")
  //        gCharAt(1) = FLUnicodeString("BC")
  //        gCharAt(2) = FLUnicodeString("D")
  //        gCharAt(3) = FLUnicodeString("E")
  FLUnicodeString gCharAt(int graphemeIndex) const;
  
  // Search this string for unmatched surrogates and replace them with the unicode replacement
  // character, returning a new string with the fixed result.
  FLUnicodeString fixedString() const;
  
  FLUnicodeString normalizedString() const;
  FLUnicodeString lowerCaseString() const;
  FLUnicodeString upperCaseString() const;
  FLUnicodeString titleCaseString() const;
  FLUnicodeString onlyLettersString() const;
  
  FLUnicodeString ltrim() const;
  FLUnicodeString rtrim() const;
  FLUnicodeString trim() const;
  
  FLUnicodeString filter(std::function<bool(const FLUnicodeString &)> f) const;
  FLUnicodeString filterNot(std::function<bool(const FLUnicodeString &)> f) const;
  
  FLUnicodeString drop(size_t count) const;
  
  std::vector<FLUnicodeString> split(const FLUnicodeString &delim, int maxsplit = -1) const;
  
  // Return a substring of this string, including start, but not including end.
  FLUnicodeString takeFromTo(size_t start, size_t end) const;
  
  // Apply op to each grapheme of this function.
  void forEachGrapheme(std::function<void(const FLUnicodeString&)> op) const {
    for (int i = 0; i < length(); ) {
      FLUnicodeString grapheme = graphemeAtIndex(i);
      op(grapheme);
      i += grapheme.length();
    }
  }
  
  // If this strings initial characters all match other, return true, false otherwise.
  bool startsWith(const FLUnicodeString other) const;
  bool endsWith(const FLUnicodeString other) const;
  
  size_t find(const char target[], size_t from = 0) const;
  size_t find(const FLUnicodeString target, size_t from = 0) const;
  size_t rfind(const char target[], size_t from = std::string::npos) const;
  size_t rfind(const FLUnicodeString target, size_t from = std::string::npos) const;

  FLUnicodeCodePoint codePointForGraphemeAtIndex(int index) const;
  FLUnicodeCategory unicodeCategoryForGraphemeAtIndex(int index) const;
  bool isGraphemeAtIndexLowerCase(int index) const;
  bool isGraphemeAtIndexUpperCase(int index) const;
  bool isGraphemeAtIndexTitleCase(int index) const;
  bool isGraphemeAtIndexLetter(int index) const;
  bool isGraphemeAtIndexSpace(int index) const;
  bool isGraphemeAtIndexWhiteSpace(int index) const;
  bool isGraphemeAtIndexControl(int index) const;
  bool isGraphemeAtIndexClosingPunctuation(int index) const;
  bool isGraphemeAtIndexPunctuation(int index) const;
  bool isGraphemeAtIndexQuotationMark(int index) const;
  bool isGraphemeAtIndexPictograph(int index) const;

  static FLUnicodeCategory unicodeCategoryForCodePoint(FLUnicodeCodePoint codePoint);
  static bool isCodePointLowerCase(FLUnicodeCodePoint codePoint);
  static bool isCodePointUpperCase(FLUnicodeCodePoint codePoint);
  static bool isCodePointTitleCase(FLUnicodeCodePoint codePoint);
  static bool isCodePointLetter(FLUnicodeCodePoint codePoint);
  static bool isCodePointSpace(FLUnicodeCodePoint codePoint);
  static bool isCodePointWhiteSpace(FLUnicodeCodePoint codePoint);
  static bool isCodePointControl(FLUnicodeCodePoint codePoint);
  static bool isCodePointClosingPunctuation(FLUnicodeCodePoint codePoint);
  static bool isCodePointPunctuation(FLUnicodeCodePoint codePoint);
  static bool isCodePointQuotationMark(FLUnicodeCodePoint codePoint);
  static bool isCodePointPictograph(FLUnicodeCodePoint codePoint);

  FLUnicodeString &operator= (const FLUnicodeString & __rhs) { this->assign(__rhs.data(), __rhs.size()); return(*this); }
  FLUnicodeString &operator= (const char __rhs[])            { this->setToUTF8String((const unsigned char *)__rhs); return(*this); }
  FLUnicodeString &operator= (const unsigned char __rhs[])   { this->setToUTF8String(__rhs); return(*this); }
  
  FLUnicodeString &operator+=(const FLUnicodeString & __rhs) { this->append(__rhs.data(), __rhs.size()); return(*this); }
  FLUnicodeString &operator+=(int __rhs)                     { uint16_t c = (uint16_t)__rhs; this->append(&c, 1); return(*this); }
  FLUnicodeString &operator+=(const char __rhs[])            { FLUnicodeString __r; __r.setToUTF8String((const unsigned char *)__rhs); *this += __r; return(*this); }
  FLUnicodeString &operator+=(const std::string __rhs)       { return (*this) += __rhs.c_str(); }
  
  FLUnicodeString  operator+ (const FLUnicodeString & __rhs) const { FLUnicodeString __r; __r.assign(this->data(), this->size()); __r.append(__rhs.data(), __rhs.size()); return(__r); }
  FLUnicodeString  operator+ (const char __rhs[])            const { FLUnicodeString __r; __r.assign(this->data(), this->size()); __r += __rhs; return(__r); }

  friend FLUnicodeString  operator+ (const char __rhs[], const FLUnicodeString & __lhs) { FLUnicodeString __r(__rhs); __r += __lhs; return(__r); }

  bool operator==(const char rhs)   const { const uint16_t *chars = this->data(); return(((this->length() == 1) && (chars[0] < 256) && (((char)chars[0]) == rhs)) ? true : false); }
  bool operator==(const char rhs[]) const { const char *utf8String = this->c_str(); return(strcmp(rhs, (utf8String == NULL) ? "" : utf8String) == 0 ? true : false); }

  bool operator!=(const char rhs)   const { const uint16_t *chars = this->data(); return(((this->length() == 1) && (chars[0] < 256) && (((char)chars[0]) == rhs)) ? false : true); }
  bool operator!=(const char rhs[]) const { const char *utf8String = this->c_str(); return(strcmp(rhs, (utf8String == NULL) ? "" : utf8String) == 0 ? false : true); }
};

std::ostream& operator<<(std::ostream &os, const FLUnicodeString &s);

struct FLUnicodeStringHash {
  std::size_t operator()(const FLUnicodeString& k) const {
    std::size_t hash = 0x920b5217UL, len = k.length();
    for(size_t idx = 0; idx < len; idx++) { hash *= 0x811C9DC5; hash ^= k[idx]; }
    return(hash);
  }
};

struct FLUnicodeStringEqual {
  bool operator()(const FLUnicodeString& lhs, const FLUnicodeString& rhs) const { return((lhs.length() != rhs.length()) ? false : (memcmp(lhs.data(), rhs.data(), lhs.length() * sizeof(uint16_t)) == 0) ? true : false); }
};

template<class Value>
class FLUnicodeMap {
public:
  typedef typename std::unordered_map<FLUnicodeString, Value, FLUnicodeStringHash, FLUnicodeStringEqual> Type;
};

extern FLUnicodeString subStr(const FLUnicodeString &str, int graphemeIndexStart, int stride);

std::vector<FLUnicodeString> split(const FLUnicodeString &s, const FLUnicodeString& delims);

typedef std::unordered_map<FLUnicodeString, FLPoint, FLUnicodeStringHash, FLUnicodeStringEqual> FLUnicodeStringToPointMap;

struct FLPointComp {
  bool operator() (const FLPoint& lhs, const FLPoint& rhs) const { return((lhs.x < rhs.x) ? true : (lhs.x > rhs.x) ? false : (lhs.y < rhs.y) ? true : false); }
};
typedef std::map<FLPoint, std::vector<FLUnicodeString>, FLPointComp> FLPointToCharVectorMap;

#endif /* defined(__FleksySDK__FLUnicodeString__) */
