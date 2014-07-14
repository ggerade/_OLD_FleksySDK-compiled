//
//  FLEnums.h
//  FleksySDK
//
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK_FLEnums_h__
#define __FleksySDK_FLEnums_h__

enum FLABTestType{
  FLABTestType_Engine,
  FLABTestType_Disabled
};

enum FLABTestMode {
  FLABTestMode_A,
  FLABTestMode_B,
};

enum FLDictionaryWordType {
  FLDictionaryWordType_DAWG,
  FLDictionaryWordType_USER,
  FLDictionaryWordType_NOT_FOUND
};

enum FLCapitalizationMode{
  FLCapitalizationMode_CAP_SENTENCES,
  FLCapitalizationMode_CAP_WORDS,
  FLCapitalizationMode_CAP_ALL,
  FLCapitalizationMode_CAP_OFF
};

typedef enum{
  FLKeyboardID_QWERTY_LOWER,
  FLKeyboardID_QWERTY_UPPER,
  FLKeyboardID_NUMBERS,
  FLKeyboardID_SYMBOLS,
  FLKeyboardID_QWERTY_AC_OFF,
  FLKeyboardID_EMOJIS,
  FLKeyboardID_NUMBER_PAD,
  FLKeyboardID_NUMBER_PAD_SYMBOLS,
  FLKeyboardID_NUMBER_OF_KEYBOARDS
}FLKeyboardID;

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
  FLFieldAction_EMOTICON,
  FLFieldAction_NONE
};

typedef enum{
  FLKeyboardSize_ORIGINAL,
  FLKeyboardSize_SMALL,
  FLKeyboardSize_TINY,
  FLKeyboardSize_NOT_SET
}FLKeyboardSize;

enum FLKeyboardLayout{
  FLKeyboardLayout_NO_SPACEBAR,
  FLKeyboardLayout_SPACEBAR,
  FLKeyboardLayout_NOT_SET
};

enum FLKeyboardAlpha{
  FLKeyboardAlpha_FULL,
  FLKeyboardAlpha_TRANSPARENT,
  FLKeyboardAlpha_NOT_SET
};

enum FLMessageType{
  FLMessageType_DEBUG,
  FLMessageType_NO_NEXT_SUGGESTION,
  FLMessageType_NO_PREVIOUS_SUGGESTION,
  FLMessageType_EVENT,
  FLMessageType_ERROR,
  FLMessageType_BACKSPACE,
  FLMessageType_UPLOAD_DATA_FILE,
  FLMessageType_SPACEBAR_STATE_PUNCTUATION,
  FLMessageType_SPACEBAR_STATE_CLEAR,
};

//passed in as a parameter in onDictionaryModified
enum FLDictionaryChangeEvent{
  FLDictionaryChangeEvent_ADD,
  FLDictionaryChangeEvent_REMOVE,
  FLDictionaryChangeEvent_WORD_AUTOLEARNED
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
  FLTextFieldType_NO_SUGGESTIONS,
  FLTextFieldType_USER_AC_OFF
};

enum FLLongPressType{
  FLLongPressType_NONE,
  FLLongPressType_LONG_PRESS
};

enum FLSuggestionsType{
  FLSuggestionsType_REGULAR,
  FLSuggestionsType_PUNCTUATION,
  FLSuggestionsType_CLEAR_SUGGESTIONS //UI should clear the suggestions
};

enum FLEventType{
  FLEventType_SL,
  FLEventType_SR,
  FLEventType_SU,
  FLEventType_SD,
  FLEventType_RSW,
  FLEventType_RSP,
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
  FLEventType_LP,
  FLEventType_WT,
  FLEventType_ATW,
  FLEventType_ALW,
  FLEventType_NEW_WORD,
  FLEventType_SEL_SUGGESTION_0,
  FLEventType_CC, //Characters Corrected
  FLEventType_WC,  //Word Corrected
  FLEventType_WC_INTERNAL,  //Word Corrected
  FLEventType_MISSED_ALL_CHARS,
  FLEventType_SEL_DEL,
  FLEventType_REPARSE,
  FLEventType_TD, //Text block deleted
  FLEventType_TI,
  FLEventType_SUW,
  FLEventType_SUP,
  FLEventType_SDW,
  FLEventType_SDP,
  FLEventType_TBS
};

#endif /* defined(__FleksySDK_FLEnums_h__) */
