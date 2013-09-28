//
//  TimeFunctions.h
//  FleksyContext
//
//  Created by Kostas Eleftheriou on 1/4/13.
//  Copyright (c) 2013 Syntellia Inc. All rights reserved.
//

// TODO refactor this with FleksyEngine files

#ifndef FleksyContext_TimeFunctions_h
#define FleksyContext_TimeFunctions_h


#include <PatternRecognizer/Structures.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>

using namespace std;

struct timespec fl_get_timespec();
double fl_get_time();

vector<FLString> split(const FLString &s, const FLString& delims);



// trim from start
static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}

// trim punctuation

int fl_ispunct(int c);

// trim from start
static inline std::string &ltrim_punct(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(fl_ispunct))));
  return s;
}

// trim from end
static inline std::string &rtrim_punct(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(fl_ispunct))).base(), s.end());
  return s;
}


/* // trim from start */
/* static inline std::string &ltrim_punct(std::string &s) { */
/*   s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::ispunct)))); */
/*   return s; */
/* } */

/* // trim from end */
/* static inline std::string &rtrim_punct(std::string &s) { */
/*   s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::ispunct))).base(), s.end()); */
/*   return s; */
/* } */

// trim from both ends
static inline std::string &trim_punct(std::string &s) {
  return ltrim_punct(rtrim_punct(s));
}


#endif
