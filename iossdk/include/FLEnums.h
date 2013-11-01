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
  FLKeyboardID_QWERTY_AC_OFF,
  FLKeyboardID_NUMBER_OF_KEYBOARDS
};

enum FLCorrectionMode{
  FLCorrectionMode_URL, //In this mode, when . is entered previous TB is not corrected
  FLCorrectionMode_ALWAYS,
  FLCorrectionMode_OFF
};

enum FLFieldAction{
  FLFieldAction_SEARCH,
  FLFieldAction_GO,
  FLFieldAction_NEXT,
  FLFieldAction_SEND,
  FLFieldAction_NEW_LINE,
  FLFieldAction_DONE,
  FLFieldAction_EMOTICON
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
  FLMessageType_UPLOAD_DATA_FILE,
  FLMessageType_LAST_CHARACTER_DELETED
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

enum FLPunctuationSpaceMode{
  //On manual punctuation
  FLPunctuationSpaceMode_DEFAULT, //[hello]+ -> [hello]+[.]-[|]
  FLPunctuationSpaceMode_DEL_PRECEEDING_SPACE, //[hello]+ -> [hello]-[.]-[|]
  FLPunctuationSpaceMode_ADD_SPACE_AFTER, //[hello]+ -> [hello]+[.]+[|]
  FLPunctuationSpaceMode_DEL_AND_ADD_SPACE //[hello]+ -> [hello]-[.]+[|]
};

enum FLTextFieldType{
  FLTextFieldType_REGULAR_TEXT,
  FLTextFieldType_PASSWORD,
  FLTextFieldType_URL,
  FLTextFieldType_NO_SUGGESTIONS
};

enum FLLongPressType{
  FLLongPressType_NONE,
  FLLongPressType_LONG_PRESS
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
  FLEventType_ME,
  FLEventType_DEL,
  FLEventType_ST,
  FLEventType_ET,
  FLEventType_FA,
};

#endif /* defined(__FleksySDK_FLEnums_h__) */
