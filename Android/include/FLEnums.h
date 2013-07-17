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
  FLCorrectionMode_URL, //In this mode, when . is entered previous TB is not corrected
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
  FLMessageType_ERROR,
  FLMessageType_BACKSPACE,
  FLMessageType_UPLOAD_DATA_FILE
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

enum FLDeleteMode{
  FLDeleteMode_VARIABLE,
  FLDeleteMode_WHOLE_WORD
};

enum FLEventType{
  FLEventType_SL,
  FLEventType_SR,
  FLEventType_SU,
  FLEventType_SD,
  FLEventType_RS,
  FLEventType_P,
  FLEventType_MC,
  FLEventType_SH,
  FLEventType_KB,
  FLEventType_STS,
  FLEventType_ETS,
  FLEventType_LC,
  FLEventType_CAPS,
  FLEventType_AW,
  FLEventType_RW,
  FLEventType_AC,
  FLEventType_MS,
  FLEventType_NL,
  FLEventType_KS,
  FLEventType_ME
};

#endif /* defined(__FleksySDK_FLEnums_h__) */
