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
#include <sstream>

#include "FleksySDKVersion.h"

extern "C" {
extern char *(*fl_backtrace)(void);
}

namespace Fleksy {

class exception : public std::exception {

protected:
  std::string message_;
  std::string whatString_;
  std::string backtraceString_;
  std::string fileString_;
  int lineNumber_ = 0;

  void init(const char *file, int lineNumber, std::string msg) {
    backtraceString_ = fl_backtrace();
    if(file != NULL) {
      fileString_ = file;
    }
    lineNumber_ = lineNumber;
    message_ = msg;
    
    std::stringstream ss;
    if (!fileString_.empty()) {
      ss << "<" << fileString_ << ":" << lineNumber_ << "> ";
    }
    ss << (message_.empty() ? "<NO MESSAGE>" : message_) << "\n";
    ss << "Version: " << fleksySDKBuildGitShortHash << "-" << fleksySDKBuildUser << "@" << fleksySDKBuildDate << "\n";
    ss << backtraceString_;
  }
  
  void vinit(const char *file, int lineNumber, const char *message, va_list args) {
    char *vmessage = NULL;
    vasprintf(&vmessage, message == NULL ? "<NULL>" : message, args);
    init(file, lineNumber, vmessage);
    if(vmessage != NULL) { free(vmessage); vmessage = NULL; }
  }

public:

  explicit exception(const std::string &message)                                   { init(NULL,         -1, message.c_str()); }
  explicit exception(const char *file, int lineNumber, const std::string &message) { init(file, lineNumber, message.c_str()); }
  explicit exception(const char *message, ...)                                     { va_list args; va_start(args, message); va_end(args); vinit(NULL,         -1, message, args); }
  explicit exception(const char *file, int lineNumber, const char *message, ...)   { va_list args; va_start(args, message); va_end(args); vinit(file, lineNumber, message, args); }
  
  virtual const char *what() const throw () {
    return(whatString_.c_str());
  }
  
  std::string message() const {
    return message_;
  }
  
  std::string backtrace() const {
    return backtraceString_;
  }
};

}

#define FLException(msg, ...) Fleksy::exception(__FILE__, __LINE__, msg, ##__VA_ARGS__)
#define EXassert(condition) if (!(condition)) { throw FLException("Assertion failed! <" #condition ">"); }

#endif /* defined(__FleksySDK__FLException__) */
