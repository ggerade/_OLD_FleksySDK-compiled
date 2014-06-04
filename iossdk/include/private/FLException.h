//
//  FLException.h
//  FleksySDK
//
//  Created by John Engelhart on 9/16/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLException__
#define __FleksySDK__FLException__

#include <exception>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FleksySDKVersion.h"

extern "C" {
  extern char *(*fl_backtrace)(void);
}




namespace Fleksy {
  
  class Exception : public std::exception {
  protected:
    std::string _message;
    std::string _backtrace;
    std::string _filename;
    std::string _what;
    int _lineNumber;
    
    void init(const std::string message, std::string filename, int lineNumber) {
      const auto backtraceString = fl_backtrace();
      char *whatCString = nullptr;
      asprintf(&whatCString,
               "<%s:%d> %s\n\nVersion: %s-%s@%s\n%s",
               filename.c_str(),
               lineNumber,
               message.c_str(),
               fleksySDKBuildGitShortHash,
               fleksySDKBuildUser,
               fleksySDKBuildDate,
               (backtraceString == nullptr) ? "<UNAVAILABLE>" : backtraceString);
      
      _what = std::string(whatCString);
      
      if (whatCString != nullptr) {
        free(whatCString);
        whatCString = nullptr;
      }
    }
    
  public:
    
    std::string message()    const { return _message; }
    std::string backtrace()  const { return _backtrace; }
    std::string filename()   const { return _filename; }
    int         lineNumber() const { return _lineNumber; }
    const char* what() const throw() override { return _what.c_str(); }
  };
  
  
  
  
  class PlainException : public Exception {
  public:
    explicit PlainException(std::string message, std::string filename = "", int lineNumber = 0) {
      init(message, filename, lineNumber);
    }
  };
  
  class InvalidArguments : public Exception {
  public:
    explicit InvalidArguments(std::string message, std::string filename = "", int lineNumber = 0) {
      init(message, filename, lineNumber);
    }
  };
  
  class IOError : public Exception {
  public:
    explicit IOError(std::string message, std::string filename = "", int lineNumber = 0) {
      init(message, filename, lineNumber);
    }
  };
  
  template <typename E>
  E vaGenerateException(const char *file, int lineNumber, const char *message, ...) {
    try {
      char _vaBuffer[50000];
      
      va_list(args);
      va_start(args, message);
      int result = vsnprintf(_vaBuffer, sizeof(_vaBuffer), (message == nullptr) ? "<NULL>" : message, args);
      va_end(args);
      
      if (result == -1) {
        strcpy(_vaBuffer, message);
      }
      
      E e(std::string(_vaBuffer), file, lineNumber);
      _vaBuffer[0] = 0;
      return e;
    }
    catch (const std::exception &e) {
      return E("Problem creating exception.", file, lineNumber);
    }
  }
}

#define FLMagicException(type, msg, ...) Fleksy::vaGenerateException<type>(__FILE__, __LINE__, msg, ##__VA_ARGS__)
#define FLException(msg, ...) FLMagicException(Fleksy::PlainException, msg, ##__VA_ARGS__)
#define InvalidArguments(msg, ...) FLMagicException(Fleksy::InvalidArguments, msg, ##__VA_ARGS__)
#define IOError(msg, ...) FLMagicException(Fleksy::IOError, msg, ##__VA_ARGS__)

#endif /* defined(__FleksySDK__FLException__) */
