//
//  Platform.h
//  PatternRecognizer
//
//  Created by Kostas Eleftheriou on 12/12/12.
//  Copyright (c) 2012 Syntellia Inc. All rights reserved.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef FLEKSYNOLOGGING
#define LOGI(...)
#else
#ifdef ANDROID
#include <android/log.h>
#define  LOG_TAG    "Fleksy Native C++"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#else
#if RELEASE
#define  LOGI(format, ...)
#else
#define  LOGI(format, ...)  printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout)
//#define  LOGI(format, ...)  {char buffer[1024 * 10]; snprintf(buffer, sizeof(buffer), format,##__VA_ARGS__); std::cout << buffer << std::endl; }
#endif
#endif
#endif


//#define FLassert(condition) assert(condition)
#define FLassert(condition) { if(!(condition)){ signalHandlerWithParams(-3, #condition, __func__, __FILE__, __LINE__); } }


#define FLEKSY_LIBRARY_EXPIRES 0
//http://www.ruddwire.com/handy-code/date-to-millisecond-calculators/
//Tue Apr 30 2013 00:00:00 GMT-0700 (PDT)
#define EXPIRATION_DATE_IN_SECONDS 1367305200
// set to 0 to disable. Value is approximate
#define ALLOWED_REQUESTS_PER_WORD_LENGTH 0
//(10 * 1000)



class StaticVariables {
public:
  static void* listener;
  static bool aborting;
  //static struct sigaction oldHandlers[100];
};


void signalHandlerWithParams(int signal_num, const char* condition, const char* func, const char* file, int line);
void signalHandler(int signal_num);

void install_signal_handlers();
//void uninstall_signal_handlers();

#endif
