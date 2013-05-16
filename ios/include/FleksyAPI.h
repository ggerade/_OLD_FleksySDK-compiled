//
//  FleksyAPI.h
//  FleksySDK
//
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK_FleksyAPI_h__
#define __FleksySDK_FleksyAPI_h__

#include <map>
#include "FleksyListenerInterface.h"
#include "FLPoint.h"
#include "FLEnums.h"
#include "FLString.h"

class FleksyAPIpImpl;

class FleksyAPI{
  
public:
  FleksyAPI(FleksyListenerInterface &listener);
  ~FleksyAPI();
  
  /*
   * Set the resource file that will be used by loadResources(). This also loads the keyboard maps so that the client can use
   * getKeymapForKeyboard() to draw the UI before calling loadResources().
   */
  void setResourceFile(const char *file);
  
  /*
   * Loads the resources from the file set by setResourceFile().
   * After this Fleksy is ready for input.
   */
  void loadResources();
  
  /*
   * Returns FLDictionaryChangeResult_SUCCESS if the word was added, FLDictionaryChangeResult_EXISTS if the word was already in the dictionary.
   */
  FLDictionaryChangeResult addWordToDictionary(FLString word);
  
  /*
   * Returns FLDictionaryChangeResult_SUCCESS if the word was added, FLDictionaryChangeResult_NOT_FOUND if the word was not in the dictionary.
   */
  FLDictionaryChangeResult removeWordFromDictionary(FLString word);
  
  /*
   * Sets the desired keyboard frame of reference. The x and y arguments of the |sendTap| method are expected to be within this frame.
   * You should call this on initialization and whenever the keyboard size may have changed in the UI (e.g., switching between portrait
   * and landscape orientations). Note that this frame should only cover the letter keys (e.g., QWERTY...) and not any of the control
   * keys such as the spacebar.
   */
  void setPlatformKeyboardSize(float width, float height);
  
  /*
   * Takes x,y coordinates of the tap and optionally the time when tap occurred. Coordinates should be within the range set by
   * |setPlatformKeyboardSize|. This will result in a call to your FleksyListenerInterface onSetComposingText() with the character
   * that is closest to the x,y coordinates.
   */
  void sendTap(float x, float y, long long time = 0);
  
  /*
   * Adds space or <.>
   * <word> -> <word >
   * <word > -> <word. >
   */
  void space(bool buttonPress = false);
  
  /*
   * If buttonPress = true, then backspace() will delete just a single character.
   * Otherwise, what is deleted depends on the cursor position.
   * If the character before the cursor is a space after a word (i.e., <the word |>), then the space and the word will be deleted (i.e., <the |>).
   * If the cursor is in the middle of a word (i.e., <wor|d >), then only a single character will be deleted (i.e., <the wo|d >).
   */
  void backspace(bool buttonPress = false);
  
  /*
   * Replaces the current word with the previous word on the suggestion list.
   * Note: If the cursor is in the middle of a word the cursor will be moved to the end of the previous suggestion replacement word (i.e., <wor|d1 > -> <word0 |>).
   */
  void previousSuggestion();
  
  /*
   * Replaces current word with the next word on the suggestion list.
   * Note: If the cursor is in the middle of a word the cursor will be moved to the end of the next suggestion replacement word (i.e., <wor|d0 > -> <word1 |>).
   */
  void nextSuggestion();
  
  /*
   * Will send '\n' as entered text.
   */
  void enter();
  
  /*
   * Set the cursor position. If cursorUpdates are not simulated this needs to be called with the new cursor position every time the cursor moves.
   */
  void cursorSelectionChanged(int selectionStart, int selectionEnd);
  
  /*
   * Let Fleksy know that a change has occurred in the text editor caused by external source (e.g., new text was pasted by the user).
   */
  void startTypingSession(bool platformMovesCursor = false);
  
  /*
   * Call this when the user is done with entering text(closed app/keyboard)
   * IMPORTANT: After calling endTypingSession(), startTypingSession() must be called before making any other calls to the API.
   */
  void endTypingSession();
  
  /*
   * Sets the capitalization mode. By default FLCapitalizationMode_CAP_SENTENCES which will capitalize first character of each sentence.
   * Other modes:
   * FLCapitalizationMode_CAP_WORDS          - capitalize the first character of all words.
   * FLCapitalizationMode_CAP_ALL            - capitalize all characters. (aka: Caps Lock)
   * FLCapitalizationMode_CAP_SENTENCES      - capitalize first character of every sentence
   * FLCapitalizationMode_CAP_OFF            - nothing will be capitalized automatically
   */
  void setCapitalizationMode(FLCapitalizationMode mode);
  
  /*
   * Set the keyboard the user is on: QWERTY, SYMBOLS, NUMBERS.
   */
  void setActiveKeyboard(FLKeyboardID keyboardID);
  
  /*
   * Returns active keyboard.
   * FLKeyboardID_QWERTY_UPPER  (1)
   * FLKeyboardID_NUMBERS (2)
   * FLKeyboardID_SYMBOLS (3)
   */
  FLKeyboardID getActiveKeyboardID();
  
  /*
   * Returns a keymap for KeyboardID containing the keyboards characters and their locations on the screen.
   */
  std::map<FLChar, FLPoint> getKeymapForKeyboard(FLKeyboardID keyboardID);
  
  /*
   * Sets the correction mode.
   * FLCorrectionMode_ALWAYS = ON
   * FLCorrectionMode_OFF will not make corrections and will only delete a single character at a time.
   */
  void setCorrectionMode(FLCorrectionMode mode);
  
  /*
   * You can use this to send additional hints to Fleksy as to what rawText should be corrected to.
   * These suggestions will be considered in the response.
   */
  void setAdditionalSuggestions(FLString rawText, FLString suggestionList);
  
  /*
   * Returns a boolean value that indicates whether or not Fleksy knows a word.
   */
  bool knowsWord(FLString word);
  
  /*
   * Sets whether voice feedback is enabled.
   */
  void setVoiceFeedback(bool voiceFeedbackEnabled);
  
  /*
   * Toggles whether the shift button is pressed.
   */
  void toggleShift();
  
  std::string getVersion();
  
  //private:
  FleksyAPIpImpl *pImpl;
};


#endif /* defined(__FleksySDK_FleksyAPI_h__) */
