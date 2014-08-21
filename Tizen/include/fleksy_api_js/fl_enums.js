
var FLABTestType_enum = {
  FLABTestType_Engine: 0,
  FLABTestType_Disabled: 1
};

var FLABTestMode_enum = {
  FLABTestMode_A: 0,
  FLABTestMode_B: 1
};

var FLDictionaryWordType_enum = {
  FLDictionaryWordType_DAWG: 0,
  FLDictionaryWordType_USER: 1,
  FLDictionaryWordType_NOT_FOUND: 2
};

var FLCapitalizationMode_enum = {
  FLCapitalizationMode_CAP_SENTENCES: 0,
  FLCapitalizationMode_CAP_WORDS: 1,
  FLCapitalizationMode_CAP_ALL: 2,
  FLCapitalizationMode_CAP_OFF: 3
};

var FLKeyboardID_enum = {
  FLKeyboardID_QWERTY_LOWER: 0,        // 0
  FLKeyboardID_QWERTY_UPPER: 1,        // 1
  FLKeyboardID_NUMBERS: 2,             // 2
  FLKeyboardID_SYMBOLS: 3,             // 3
  FLKeyboardID_QWERTY_AC_OFF: 4,       // 4
  FLKeyboardID_EMOJIS: 5,              // 5
  FLKeyboardID_NUMBER_PAD: 6,          // 6
  FLKeyboardID_NUMBER_PAD_SYMBOLS: 7,  // 7
  FLKeyboardID_SHIFT_1: 8,             // 8
  FLKeyboardID_SHIFT_2: 9,             // 9
  FLKeyboardID_SHIFT_3: 10,             // 10
  FLKeyboardID_NUMBER_OF_KEYBOARDS: 11
};

var FLCorrectionMode_enum = {
  FLCorrectionMode_URL: 0, //In this mode, when . is entered previous TB is not corrected
  FLCorrectionMode_ALWAYS: 1,
  FLCorrectionMode_OFF: 2
};

var FLFieldAction_enum = {
  FLFieldAction_SEARCH: 0,
  FLFieldAction_GO: 1,
  FLFieldAction_NEXT: 2,
  FLFieldAction_SEND: 3,
  FLFieldAction_NEW_LINE: 4,
  FLFieldAction_DONE: 5,
  FLFieldAction_EMOTICON: 6,
  FLFieldAction_NONE: 7
};

var FLKeyboardSize_enum = {
  FLKeyboardSize_ORIGINAL: 0,
  FLKeyboardSize_SMALL: 1,
  FLKeyboardSize_TINY: 2,
  FLKeyboardSize_NOT_SET: 3
};

var FLKeyboardLayout_enum = {
  FLKeyboardLayout_NO_SPACEBAR: 0,
  FLKeyboardLayout_SPACEBAR: 1,
  FLKeyboardLayout_NOT_SET: 2
};

var FLKeyboardAlpha_enum = {
  FLKeyboardAlpha_FULL: 0,
  FLKeyboardAlpha_TRANSPARENT: 1,
  FLKeyboardAlpha_NOT_SET: 2
};

var FLMessageType_enum = {
  FLMessageType_DEBUG: 0,
  FLMessageType_NO_NEXT_SUGGESTION: 1,
  FLMessageType_NO_PREVIOUS_SUGGESTION: 2,
  FLMessageType_EVENT: 3,
  FLMessageType_ERROR: 4,
  FLMessageType_ERROR1: 5,
  FLMessageType_ERROR2: 6,
  FLMessageType_ERROR3: 7,
  FLMessageType_BACKSPACE: 8,
  FLMessageType_UPLOAD_DATA_FILE: 9,
  FLMessageType_SPACEBAR_STATE_PUNCTUATION: 10,
  FLMessageType_SPACEBAR_STATE_CLEAR: 11
};

//passed in as a parameter in onDictionaryModified
var FLDictionaryChangeEvent_enum = {
  FLDictionaryChangeEvent_ADD: 0,
  FLDictionaryChangeEvent_REMOVE: 1,
  FLDictionaryChangeEvent_WORD_AUTOLEARNED: 2
};


var FLDictionaryChangeResult_enum = {
  FLDictionaryChangeResult_SUCCESS: 0,
  FLDictionaryChangeResult_EXISTS: 1,
  FLDictionaryChangeResult_NOT_FOUND: 2,
  FLDictionaryChangeResult_ERROR: 3
};

var FLDeleteMode_enum = {
  FLDeleteMode_VARIABLE: 0,
  FLDeleteMode_WHOLE_WORD: 1
};

var FLPunctuationSpaceMode_enum = {
  //On manual punctuation
  FLPunctuationSpaceMode_DEFAULT: 0, //[hello]+ -> [hello]+[.]-[|]
  FLPunctuationSpaceMode_DEL_PRECEEDING_SPACE: 1, //[hello]+ -> [hello]-[.]-[|]
  FLPunctuationSpaceMode_DEL_AND_ADD_SPACE: 2 //[hello]+ -> [hello]-[.]+[|]
};

var FLTextFieldType_enum = {
  FLTextFieldType_REGULAR_TEXT: 0,
  FLTextFieldType_PASSWORD: 1,
  FLTextFieldType_URL: 2,
  FLTextFieldType_NO_SUGGESTIONS: 3,
  FLTextFieldType_USER_AC_OFF: 4
};

var FLLongPressType_enum = {
  FLLongPressType_NONE: 0,
  FLLongPressType_LONG_PRESS: 1
};

var FLSuggestionsType_enum = {
  FLSuggestionsType_REGULAR: 0,
  FLSuggestionsType_PUNCTUATION: 1,
  FLSuggestionsType_CLEAR_SUGGESTIONS: 2 //UI should clear the suggestions
}

//enum {
//  FLEventType_SL,
//  FLEventType_SR,
//  FLEventType_SU,
//  FLEventType_SD,
//  FLEventType_RSW,
//  FLEventType_RSP,
//  FLEventType_P,
//  FLEventType_MC,
//  FLEventType_SH,
//  FLEventType_KB,
//  FLEventType_STS,
//  FLEventType_ETS,
//  FLEventType_LC,
//  FLEventType_CAPS,
//  FLEventType_AW,
//  FLEventType_RW,
//  FLEventType_AC,
//  FLEventType_MS,
//  FLEventType_NL,
//  FLEventType_KS,
//  FLEventType_ME,
//  FLEventType_DEL,
//  FLEventType_ST,
//  FLEventType_ET,
//  FLEventType_FA,
//  FLEventType_LP,
//  FLEventType_WT,
//  FLEventType_ATW,
//  FLEventType_ALW,
//  FLEventType_NEW_WORD,
//  FLEventType_SEL_SUGGESTION_0,
//  FLEventType_CC, //Characters Corrected
//  FLEventType_WC,  //Word Corrected
//  FLEventType_WC_INTERNAL,  //Word Corrected
//  FLEventType_MISSED_ALL_CHARS,
//  FLEventType_SEL_DEL,
//  FLEventType_REPARSE,
//  FLEventType_TD, //Text block deleted
//  FLEventType_TI,
//  FLEventType_SUW,
//  FLEventType_SUP,
//  FLEventType_SDW,
//  FLEventType_SDP,
//  FLEventType_TBS
//};

