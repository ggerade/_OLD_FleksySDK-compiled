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
  
  class exception : public std::exception {
    
  protected:
    char *message_         = NULL;
    char *whatCString_     = NULL;
    char *backtraceString_ = NULL;
    char *fileString_      = NULL;
    int   lineNumber_      = 0;
    
    void init(const char *file, int lineNumber, const char *message) {
      backtraceString_ = fl_backtrace();
      if(file != NULL) { fileString_ = strdup(file); }
      lineNumber_ = lineNumber;
      if(message != NULL) { message_ = strdup(message); }
      asprintf(&whatCString_, "<%s:%d> %s\n\nVersion: %s-%s@%s\n%s", (fileString_ == NULL) ? "<NULL>" : fileString_, lineNumber_, (message_ == NULL) ? "<NULL>" : message_, fleksySDKBuildGitShortHash, fleksySDKBuildUser, fleksySDKBuildDate, (backtraceString_ == NULL) ? "<UNAVAILABLE>" : backtraceString_);
    }
    void vinit(const char *file, int lineNumber, const char *message, va_list args) {
      char *vmessage = NULL;
      vasprintf(&vmessage, (message == NULL) ? "<NULL>" : message, args);
      init(file, lineNumber, vmessage);
      if(vmessage != NULL) { free(vmessage); vmessage = NULL; }
    }
    
  public:
    
    explicit exception(const std::string &message)                                   { init(NULL,         -1, message.c_str()); }
    explicit exception(const char *file, int lineNumber, const std::string &message) { init(file, lineNumber, message.c_str()); }
    explicit exception(const char *message, ...)                                     { va_list args; va_start(args, message); vinit(NULL,         -1, message, args); va_end(args); }
    explicit exception(const char *file, int lineNumber, const char *message, ...)   { va_list args; va_start(args, message); vinit(file, lineNumber, message, args); va_end(args); }
    virtual ~exception() throw () {
      if(whatCString_     != NULL) { free((void *)whatCString_);     whatCString_     = NULL; }
      if(backtraceString_ != NULL) { free((void *)backtraceString_); backtraceString_ = NULL; }
      if(fileString_      != NULL) { free((void *)fileString_);      fileString_      = NULL; }
      if(message_         != NULL) { free((void *)message_);         message_         = NULL; }
    }
    virtual const char *what()    const throw () { return(whatCString_); }
    virtual const char *message() const throw () { return(message_);     }
    
    exception &operator= (const exception &__rhs) {
      if(__rhs.message_         != NULL) { message_         = strdup(__rhs.message_);         }
      if(__rhs.whatCString_     != NULL) { whatCString_     = strdup(__rhs.whatCString_);     }
      if(__rhs.backtraceString_ != NULL) { backtraceString_ = strdup(__rhs.backtraceString_); }
      if(__rhs.fileString_      != NULL) { fileString_      = strdup(__rhs.fileString_);      }
      lineNumber_ = __rhs.lineNumber_;
      
      return(*this);
    }
  };
  
}

#define FLException(msg, ...) Fleksy::exception(__FILE__, __LINE__, msg, ##__VA_ARGS__)

#endif /* defined(__FleksySDK__FLException__) */
