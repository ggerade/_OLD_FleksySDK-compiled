//
//  FLEnums.h
//  FleksyLib
//
//  Created by Vadim Maximov on 3/19/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FleksyLib_FLEnums_h
#define FleksyLib_FLEnums_h


enum FLCapitalizationMode{
    FLCapitalizationMode_CAP_SENTENCES,
    FLCapitalizationMode_CAP_NEXT_CHAR_ONLY,
    FLCapitalizationMode_CAP_WORDS,
    FLCapitalizationMode_CAP_ALL
};

enum FLKeyboardID{
    FLKeyboardID_QWERTY,
    FLKeyboardID_NUMBERS,
    FLKeyboardID_SYMBOLS,
};


enum FLCorrectionMode{
   FLCorrectionMode_ALWAYS,
   FLCorrectionMode_OFF
};

enum FLMessageType{
    FLMessageType_USER,
    FLMessageType_DEBUG,
    FLMessageType_NO_NEXT_SUGGESTION,
    FLMessageType_NO_PREVIOUS_SUGGESTION,
    FLMessageType_EXIT
};

enum FLDictionaryChangeEvent{
    FLDictionaryChangeEvent_ADDED,
    FLDictionaryChangeEvent_ADD,
    FLDictionaryChangeEvent_REMOVED,
    FLDictionaryChangeEvent_REMOVE
};
enum FLDictionaryChangeResult{
    FLDictionaryChangeResult_SUCCESS,
    FLDictionaryChangeResult_EXISTS,
    FLDictionaryChangeResult_NOT_FOUND
};

#endif
