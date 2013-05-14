//
//  FLEnums.h
//  FleksySDK
//
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK_FLEnums_h__
#define __FleksySDK_FLEnums_h__

enum FLCapitalizationMode{
  FLCapitalizationMode_CAP_SENTENCES,
  FLCapitalizationMode_CAP_WORDS,
  FLCapitalizationMode_CAP_ALL,
  FLCapitalizationMode_CAP_OFF
};

enum FLKeyboardID{
  FLKeyboardID_QWERTY_LOWER,
  FLKeyboardID_QWERTY_UPPER,
  FLKeyboardID_NUMBERS,
  FLKeyboardID_SYMBOLS,
  FLKeyboardID_NUMBER_OF_KEYBOARDS
};

enum FLCorrectionMode{
  FLCorrectionMode_ALWAYS,
  FLCorrectionMode_OFF
};

enum FLMessageType{
  FLMessageType_DISPLAY_TO_USER,
  FLMessageType_DEBUG,
  FLMessageType_NO_NEXT_SUGGESTION,
  FLMessageType_NO_PREVIOUS_SUGGESTION,
  FLMessageType_EXIT,
  FLMessageType_EVENT,
  FLMessageType_ERROR
};

//passed in as a parameter in onDictionaryModified
enum FLDictionaryChangeEvent{
  FLDictionaryChangeEvent_ADD,
  FLDictionaryChangeEvent_REMOVE
};

//Result when called from JAVA
enum FLDictionaryChangeResult{
  FLDictionaryChangeResult_SUCCESS,
  FLDictionaryChangeResult_EXISTS,
  FLDictionaryChangeResult_NOT_FOUND,
  FLDictionaryChangeResult_ERROR
};

#endif /* defined(__FleksySDK_FLEnums_h__) */
