//
//  FLEnums.h
//  FleksySDK
//
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK_FLEnums_h__
#define __FleksySDK_FLEnums_h__

typedef enum {
  FLABTestType_Engine,
  FLABTestType_Disabled
}FLABTestType;

typedef enum  {
  FLABTestMode_A,
  FLABTestMode_B,
}FLABTestMode;

typedef enum {
  FLDictionaryWordType_DAWG,
  FLDictionaryWordType_USER,
  FLDictionaryWordType_NOT_FOUND
}FLDictionaryWordType;

typedef enum {
  FLCapitalizationMode_CAP_SENTENCES,
  FLCapitalizationMode_CAP_WORDS,
  FLCapitalizationMode_CAP_ALL,
  FLCapitalizationMode_CAP_OFF
}FLCapitalizationMode;

typedef enum {
  FLKeyboardID_QWERTY_LOWER,        // 0
  FLKeyboardID_QWERTY_UPPER,        // 1
  FLKeyboardID_NUMBERS,             // 2
  FLKeyboardID_SYMBOLS,             // 3
  FLKeyboardID_QWERTY_AC_OFF,       // 4
  FLKeyboardID_EMOJIS,              // 5
  FLKeyboardID_NUMBER_PAD,          // 6
  FLKeyboardID_NUMBER_PAD_SYMBOLS,  // 7
  FLKeyboardID_SHIFT_1,             // 8
  FLKeyboardID_SHIFT_2,             // 9
  FLKeyboardID_SHIFT_3,             // 10
  FLKeyboardID_NUMBER_OF_KEYBOARDS
}FLKeyboardID;

typedef enum {
  FLCorrectionMode_URL, //In this mode, when . is entered previous TB is not corrected
  FLCorrectionMode_ALWAYS,
  FLCorrectionMode_OFF
}FLCorrectionMode;

typedef enum {
  FLFieldAction_SEARCH,
  FLFieldAction_GO,
  FLFieldAction_NEXT,
  FLFieldAction_SEND,
  FLFieldAction_NEW_LINE,
  FLFieldAction_DONE,
  FLFieldAction_EMOTICON,
  FLFieldAction_NONE
}FLFieldAction;

typedef enum {
  FLKeyboardSize_ORIGINAL,
  FLKeyboardSize_SMALL,
  FLKeyboardSize_TINY,
  FLKeyboardSize_NOT_SET
}FLKeyboardSize;

typedef enum {
  FLKeyboardLayout_NO_SPACEBAR,
  FLKeyboardLayout_SPACEBAR,
  FLKeyboardLayout_NOT_SET
}FLKeyboardLayout;

typedef enum {
  FLKeyboardAlpha_FULL,
  FLKeyboardAlpha_TRANSPARENT,
  FLKeyboardAlpha_NOT_SET
}FLKeyboardAlpha;

typedef enum {
  FLMessageType_DEBUG,
  FLMessageType_NO_NEXT_SUGGESTION,
  FLMessageType_NO_PREVIOUS_SUGGESTION,
  FLMessageType_EVENT,
  FLMessageType_ERROR,
  FLMessageType_ERROR1,  // FLAsyncDawgManager::build (result was invalid dawg)
  FLMessageType_ERROR2,
  FLMessageType_ERROR3,  // FLTextBlockCursor::updateToPosition
  FLMessageType_ERROR4,  // FLTypingController::deleteCharacterAt
  FLMessageType_BACKSPACE,
  FLMessageType_UPLOAD_DATA_FILE,
  FLMessageType_SPACEBAR_STATE_PUNCTUATION,
  FLMessageType_SPACEBAR_STATE_CLEAR,
}FLMessageType;

//passed in as a parameter in onDictionaryModified
typedef enum {
  FLDictionaryChangeEvent_ADD,
  FLDictionaryChangeEvent_REMOVE,
  FLDictionaryChangeEvent_WORD_AUTOLEARNED
}FLDictionaryChangeEvent;

//Result when called from JAVA
typedef enum {
  FLDictionaryChangeResult_SUCCESS,
  FLDictionaryChangeResult_EXISTS,
  FLDictionaryChangeResult_NOT_FOUND,
  FLDictionaryChangeResult_ERROR
}FLDictionaryChangeResult;

typedef enum {
  FLDeleteMode_VARIABLE,
  FLDeleteMode_WHOLE_WORD
}FLDeleteMode;

typedef enum {
  //On manual punctuation
  FLPunctuationSpaceMode_DEFAULT, //[hello]+ -> [hello]+[.]-[|]
  FLPunctuationSpaceMode_DEL_PRECEEDING_SPACE, //[hello]+ -> [hello]-[.]-[|]
  FLPunctuationSpaceMode_DEL_AND_ADD_SPACE //[hello]+ -> [hello]-[.]+[|]
}FLPunctuationSpaceMode;

typedef enum {
  FLTextFieldType_REGULAR_TEXT,
  FLTextFieldType_PASSWORD,
  FLTextFieldType_URL,
  FLTextFieldType_NO_SUGGESTIONS,
  FLTextFieldType_USER_AC_OFF
}FLTextFieldType;

typedef enum {
  FLLongPressType_NONE,
  FLLongPressType_LONG_PRESS
} FLLongPressType;

typedef enum {
  FLSuggestionsType_REGULAR,
  FLSuggestionsType_PUNCTUATION,
  FLSuggestionsType_CLEAR_SUGGESTIONS //UI should clear the suggestions
}FLSuggestionsType;

typedef enum {
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
}FLEventType;

#endif /* defined(__FleksySDK_FLEnums_h__) */
