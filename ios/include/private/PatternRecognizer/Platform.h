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

//#define FLEKSYSUPERNOLOGGING

#ifdef FLEKSYSUPERNOLOGGING
#define FLEKSYNOLOGGING 1
#warning FLEKSYNOLOGGING is defined
#warning LOG_ALWAYS is disabled
#endif

#ifdef ANDROID
  #include <android/log.h>
  #define  LOG_TAG    "Fleksy Native C++"
  #define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
  #define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
  #define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
  #define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
  #define  LOG_ALWAYS(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#elif 0&&defined(__APPLE__)
#include <CoreFoundation/CFString.h>
extern "C" void NSLog(void *format, ...);
#define  LOGI(format, ...)  { CFStringRef formattedString = CFStringCreateWithFormat(NULL, NULL, CFSTR(format), ##__VA_ARGS__); CFStringRef logString = CFStringCreateWithFormat(NULL, NULL, CFSTR("%s: %@\n"), __func__, formattedString); NSLog((void *)logString); CFRelease(formattedString); CFRelease(logString); }
#define  LOGD(format, ...)  { CFStringRef formattedString = CFStringCreateWithFormat(NULL, NULL, CFSTR(format), ##__VA_ARGS__); CFStringRef logString = CFStringCreateWithFormat(NULL, NULL, CFSTR("%s: %@\n"), __func__, formattedString); NSLog((void *)logString); CFRelease(formattedString); CFRelease(logString); }
#define  LOGW(format, ...)  { CFStringRef formattedString = CFStringCreateWithFormat(NULL, NULL, CFSTR(format), ##__VA_ARGS__); CFStringRef logString = CFStringCreateWithFormat(NULL, NULL, CFSTR("%s: %@\n"), __func__, formattedString); NSLog((void *)logString); CFRelease(formattedString); CFRelease(logString); }
#define  LOGE(format, ...)  { CFStringRef formattedString = CFStringCreateWithFormat(NULL, NULL, CFSTR(format), ##__VA_ARGS__); CFStringRef logString = CFStringCreateWithFormat(NULL, NULL, CFSTR("%s: %@\n"), __func__, formattedString); NSLog((void *)logString); CFRelease(formattedString); CFRelease(logString); }

#ifndef FLEKSYSUPERNOLOGGING
#define  LOG_ALWAYS(format, ...)  { CFStringRef formattedString = CFStringCreateWithFormat(NULL, NULL, CFSTR(format), ##__VA_ARGS__); CFStringRef logString = CFStringCreateWithFormat(NULL, NULL, CFSTR("%s: %@\n"), __func__, formattedString); NSLog((void *)logString); CFRelease(formattedString); CFRelease(logString); }
#else
#define LOG_ALWAYS(...)
#endif

#else
  #define  LOGI(format, ...)  { printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout); }
  #define  LOGD(format, ...)  { printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout); }
  #define  LOGW(format, ...)  { printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout); }
  #define  LOGE(format, ...)  { printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout); }

#ifndef FLEKSYSUPERNOLOGGING
  #define  LOG_ALWAYS(format, ...)  { printf("%s:\t",__func__); printf(format,##__VA_ARGS__); printf("\n"); fflush(stdout); }
#else
  #define LOG_ALWAYS(...)
#endif

#endif

#if defined(FLEKSYNOLOGGING) || (!ANDROID && RELEASE)
#undef LOGI
#undef LOGD
#undef LOGW
#undef LOGE
#define LOGI(...)
#define LOGD(...)
#define LOGW(...)
#define LOGE(...)
#endif


#if DEBUG
#define FLassert(condition) { if(!(condition)){ signalHandlerWithParams(-3, #condition, __func__, __FILE__, __LINE__); } }
#else 
#define FLassert(condition) assert(condition)
#endif


#define FLEKSY_LIBRARY_EXPIRES 1
//http://www.ruddwire.com/handy-code/date-to-millisecond-calculators/
// shell% date -r EXPIRATION_DATE_IN_SECONDS
//Fri Jan 31 22:59:59 PST 2014
#define EXPIRATION_DATE_IN_SECONDS 1391237999
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
