//
//  Platform.h
//  PatternRecognizer
//
//  Created by Kostas Eleftheriou on 12/12/12.
//  Copyright (c) 2012 Syntellia Inc. All rights reserved.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include <assert.h>


#ifdef FLEKSYNOLOGGING
#define LOGI(...)
#define LOGD(...)
#define LOGW(...)
#define LOGE(...)
#else
#ifdef ANDROID
#include <android/log.h>
#define  LOG_TAG    "Fleksy Native C++"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#if RELEASE
#define  LOGI(format, ...)
#define  LOGD(format, ...)
#define  LOGW(format, ...)
#define  LOGE(format, ...)
#else
#define  LOGI(format, ...)  printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout)
#define  LOGD(format, ...)  printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout)
#define  LOGW(format, ...)  printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout)
#define  LOGE(format, ...)  printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout)
//#define  LOGI(format, ...)  {char buffer[1024 * 10]; snprintf(buffer, sizeof(buffer), format,##__VA_ARGS__); std::cout << buffer << std::endl; }
#endif
#endif
#endif


#if DEBUG
#define FLassert(condition) { if(!(condition)){ signalHandlerWithParams(-3, #condition, __func__, __FILE__, __LINE__); } }
#else 
#define FLassert(condition) assert(condition)
#endif


#define FLEKSY_LIBRARY_EXPIRES 1
//http://www.ruddwire.com/handy-code/date-to-millisecond-calculators/
//Jun 19 2013 11:24:48 GMT-0700 (PDT)
#define EXPIRATION_DATE_IN_SECONDS 1371666288
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
