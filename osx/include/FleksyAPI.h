//
//  FLSystemInput.h
//  FleksyApiTest
//
//  Created by Vadim Maximov on 12/10/12.
//  Copyright (c) 2012 Syntellia. All rights reserved.
//

#ifndef __FleksyAPI__
#define __FleksyAPI__

#include <map>
#include "FleksyListenerInterface.h"
#include "FLPoint.h"
#include "FLEnums.h"
#include "FLString.h"

class FleksyAPIpImpl;

class FleksyAPI{
  
public:
  FleksyAPI(FleksyListenerInterface &listener, bool platformMovesCursor = true);
  ~FleksyAPI();
  /*
   * Sets a path that will be used by the
   * loadResources() to load the library. This also loads the keyboard maps so that the client can 
   * use getKeymapForKeyboard and draw the UI, before calling loadResources.
   */
  void setResourcePath(const char* path);
  /*
   * Sets the resource file with given full path to the resource file
   */
  void setResourceFile(const char *file);
  /*
   * Loads the resources from the path set by setResourcePath
   * After this Fleksy is ready for input
   */
  void loadResources();
  /*
   * Returns FLDictionaryChangeResult_SUCCESS if word was added, FLDictionaryChangeResult_EXISTS if word is already in the dictionary
   */
  FLDictionaryChangeResult addWordToDictionary(FLString word);
  /*
   * Returns FLDictionaryChangeResult_SUCCESS if word was added, FLDictionaryChangeResult_NOT_FOUND if word is not in the dictionary
   */
  FLDictionaryChangeResult removeWordFromDictionary(FLString word);
  /*
   * Takes x, y coordinates of the tap, optionally time when tap occurred
   * This will result in call to your FleksyListenerInterface onSetComposingText() with the character
   * that is closest to the x,y coordinate.
   */
  void sendTap(float x, float y, long long time = 0);
  /*
   * Adds space or <.>
   * <word> -> <word >
   * <word > -> <word. >
   */
  void space();
  /*
   * If singleCharacterOnly = true, always deletes only 1 character
   * Otherwise, what is deleted depends on the cursor position
   * If cursor is a space after the word <word |> then space and a word will be deleted
   * if cursor is in the middle of a word <wor|d > only one character will be deleted.
   */
  void backspace(bool singleCharacterOnly = false);
  /*
   * Replaces current word with the previous word on the suggestion list
   * If cursor is in the middle of the word, cursor will be moved to the end <wor|d1 > -> <word0 |>
   */
  void previousSuggestion();
  /*
   * Replaces current word with the next word on the suggestion list
   * If cursor is in the middle of the word, cursor will be moved to the end <wor|d0 > -> <word1 |>
   */
  void nextSuggestion();
  /*
   * Will send '\n' as entered text
   */
  void enter();
  /*
   * Set the cursor position. If cursorUpdates are not simulated, then this needs to be called
   * with the new cursor position every time cursor moves.
   */
  void cursorSelectionChanged(int selectionStart, int selectionEnd, int length = 0); //<--------------------------------------------------------length???
  /*
   * Let Fleksy know that a change has occurfed in the text editor caused by external source. ex: new text was pasted by the user
   */
  void editorTextChanged();
  /*
   * Sets the capitalization mode. By default FLCapitalizationMode_CAP_SENTENCES which will capitalize first character of each sentence
   * Other modes:
   * FLCapitalizationMode_CAP_NEXT_CHAR_ONLY - capitalize next character(aka: Shift)
   * FLCapitalizationMode_CAP_WORDS - capitalize first character of all words
   * FLCapitalizationMode_CAP_ALL - capitalize all characters(aka: Caps Lock)
   */
  void setCapitalizationMode(FLCapitalizationMode mode);
  /*
   * Set the keyboard the user is on: QWERTY, SYMBOLS, NUMBERS
   */
  void setActiveKeyboard(FLKeyboardID keyboardID);
  
  /*
   * Returns active keyboard
   * FLKeyboardID_QWERTY  (1)
   * FLKeyboardID_NUMBERS (2)
   * FLKeyboardID_SYMBOLS (3)
   */
  FLKeyboardID getActiveKeyboardID();
  /*
   * Returns keymap for KeyboardID containing character and its location on the screen
   * can be used to draw keyboard.
   */
  std::map<FLChar, FLPoint> getKeymapForKeyboard(FLKeyboardID keyboardID);
  /*
   * Sets the correction mode.
   * FLCorrectionMode_ALWAYS = ON
   * FLCorrectionMode_OFF will not correct and will always delete only one character at a time
   */
  void setCorrectionMode(FLCorrectionMode mode); //FLCorrectionMode_ALWAYS, FLCorrectionMode_OFF
  /*
   * You can use this to send additional hints to Fleksy as to what rawText should be corrected to.
   * These suggestions will be considered in the response.
   */
  void setAdditionalSuggestions(FLString rawText, FLString suggestionList);
  
  /*
   * Check if Fleksy knows the word
   */
  bool knowsWord(FLString word);
  
  
  std::string getVersion();
  
  //private:
  FleksyAPIpImpl *pImpl;
};


#endif /* defined(__FleksyApi__) */
