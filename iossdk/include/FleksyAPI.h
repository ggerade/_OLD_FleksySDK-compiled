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
#include "FLUnicodeString.h"

extern const char* FL_API_VERSION;

class FleksyAPIpImpl;

class FleksyAPI{
  
public:
  FleksyAPI(FleksyListenerInterface &listener);
  ~FleksyAPI();
  
  /*
   * Set the resource file that will be used by loadResources(). This also loads the keyboard maps so that the client can use
   * getKeymapForKeyboard() to draw the UI before calling loadResources().
   */
  void setResourceFile(const char *file, FLUnicodeString keyboardName = "");
  
  /*
   * Loads the resources from the file set by setResourceFile().
   * After this Fleksy is ready for input.
   */
  void loadResources();
  
  static void dontWriteToDisk();
  static void setWritableDataDirectory(const std::string &directory);
  
  /*
   * @param wordString newline separated list of words to add.
   */
  void addWordsToDictionary(const FLUnicodeString &wordString);
  void addWordsToDictionary(const std::vector<FLUnicodeString> &words);
  
  /*
   * @param wordString newline separated list of words to add.
   */
  void removeWordsFromDictionary(const FLUnicodeString &wordString);
  void removeWordsFromDictionary(const std::vector<FLUnicodeString> &words);
  
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
   *
   * Character - character to use for with the x, y coordinates. (instead of the closest to the x,y)
   */
  void sendTap(float x, float y, long long time = 0, int offset = 0, FLUnicodeString character = "");
  
  /*
   * When length = 0, it means that the space bar was pressed, else it's considered as a Swipe Right
   * If the cursor is in the middle of the word and space bar is pressed then the word is split with the space
   * Ex: <te|st> ->space bar-> <te |st>
   * If the cursor is at the end of the word, word is corrected and/or cursor is moved to the end
   * Ex: <test|> ->space bar-><test |>
   * On swipe right word is corrected and/or cursor is moved to the end:
   * Ex: <tes|t> ->swipe right -> <test |>
   * On repeated presses, adds punctuation:
   * <word|> -> space -> <word |>
   * <word |> -> space -> <word. |>
   */
  void space(float length = 0);
  void testOnlyFakeSpace(float length = 0);
  
  /*
   * If length = 0, then backspace() will delete just a single character.
   * Otherwise, what is deleted depends on the cursor position.
   * If the character before the cursor is a space after a word (i.e., <the word |>), then the space and the word will be deleted (i.e., <the |>).
   * If the cursor is in the middle of a word (i.e., <wor|d >), then only a single character will be deleted (i.e., <the wo|d >).
   */
  void backspace(float length = 0);
  
  /*
   * Replaces the current word with the previous word on the suggestion list.
   * Note: If the cursor is in the middle of a word the cursor will be moved to the end of the previous suggestion replacement word (i.e., <wor|d1 > -> <word0 |>).
   */
  int previousSuggestion(float length = 0);
  
  /*
   * Replaces current word with the next word on the suggestion list.
   * Note: If the cursor is in the middle of a word the cursor will be moved to the end of the next suggestion replacement word (i.e., <wor|d0 > -> <word1 |>).
   */
  int nextSuggestion(float length = 0);
  
  /*
   * Will send '\n' as entered text.
   */
  void enter(float length = 0);
  
  /*
   * Set the cursor position. If cursorUpdates are not simulated this needs to be called with the new cursor position every time the cursor moves.
   */
  void cursorSelectionChanged(int selectionStart, int selectionEnd);
  
  /*
   * Let Fleksy know that a change has occurred in the text editor caused by external source (e.g., new text was pasted by the user).
   */
  void startTypingSession(bool platformMovesCursor = false);
  
  /*
   * Start typing session with extra information about the text editor and keyboard state
   */
  void startTypingSessionWithExtra(bool platformMovesCursor, FLFieldAction fieldAction, FLKeyboardSize keyboardSize, FLKeyboardLayout layout, FLKeyboardAlpha alphaState);
  
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
   * Default: FLCapitalizationMode_CAP_SENTENCES
   */
  void setCapitalizationMode(FLCapitalizationMode mode);
  
  /*
   * Returns current capitalization mode
   */
  FLCapitalizationMode getCapitalizationMode();
  
  /*
   * Set the keyboard the user is on: QWERTY, SYMBOLS, NUMBERS.
   * Optional: Set buttonPress to true if switch was caused by hitting a button to switch the keyboard
   */
  bool setActiveKeyboard(FLKeyboardID keyboardID, bool buttonPress = false);
  
  /*
   * Returns active keyboard.
   * FLKeyboardID_QWERTY_UPPER (1)
   * FLKeyboardID_NUMBERS (2)
   * FLKeyboardID_SYMBOLS (3)
   */
  FLKeyboardID getActiveKeyboardID();
  
  /*
   * Returns a keymap for KeyboardID containing the keyboards characters and their locations on the screen.
   */
  std::map<FLUnicodeString, FLPoint> getKeymapForKeyboard(FLKeyboardID keyboardID, bool includeAccents = false);
  
  FLPointToCharVectorMap getPointToCharVectorMapForKeyboard(FLKeyboardID keyboardID);

  /*
   * Returns the character nearest to the target point for the specified keyboard layout
   */
  FLUnicodeString getNearestChar(FLPoint target, FLKeyboardID keyboardID, int offset = 0);
  
  /*
   * Sets the correction mode.
   * FLCorrectionMode_ALWAYS  -Fleksy will auto correct everyting
   * FLCorrectionMode_OFF     -Will not make corrections and will only delete a single character at a time.
   * FLCorrectionMode_URL     -When . is enetered word is not corrected. User can swipe up or down to change to the next suggestion.
   * Default: FLCorrectionMode_ALWAYS
   */
  void setCorrectionMode(FLCorrectionMode mode);
  
  /*
   * Returns current correction mode
   */
  FLCorrectionMode getCorrectionMode();
  
  /*
   * Returns a boolean value that indicates whether or not Fleksy knows a word.
   */
  bool knowsWord(FLUnicodeString word);
  
  /*
   * Sets whether voice feedback is enabled.
   */
  void setVoiceFeedback(bool voiceFeedbackEnabled);
  
  /*
   * Toggles whether the shift button is pressed.
   */
  void toggleShift();
  
  bool isShifted();
  
  /*
   *
   * If 'space breaks' is enabled, then if the user misses the spacebar and types C,V,B, instead, then Fleksy might decide when appropriate
   * to split the word in two when correcting input. Example: [thisvis]->[this is]
   * Return value is new state. It it doesn't match the argument value, some error has occurred
   */
  bool setSpaceBreaksEnabled(bool value);
  /*
   * If the user misses a tap, Fleksy might add it in.
   *   eg. user types "helo", Fleksy could correct to "hello".
   * Return value is new state. It it doesn't match the argument value, some error has occurred
   */
  bool setMissingTapsEnabled(bool value);
  
  /*
   * If user types two consecutive letters out of order, Fleksy can fix that problem.
   *   eg. lsitening -> listening
   */
  bool setTranspositionsEnabled(bool value);
  
  /*
   *
   * FLDeleteMode_WHOLE_WORD on backspace(length > 0)(swipe left) will delete whole word regardless of cursor position: [hello |there] -> swipe left -> [there], [hel|lo there] -> swipe left -> [|there].
   * FLDeleteMode_VARIABLE on backspace(length > 0)(swipe left) will delete single characters when cursor is inside the word and whole words when cursor is a space after the word: [hello |there] -> swipe left -> [|there], [hel|lo there] -> swipe left -> [he|lo there].
   * Default: FLDeleteMode_VARIABLE
   */
  void setDeleteMode(FLDeleteMode mode);
  /*
   *
   * No correction will be perforemed on enter/new line in fields other than FLFieldAction_NEW_LINE
   * FLFieldAction_SEARCH     -Enter performs a "search" operation, taking the user to the results of searching for the text the have typed (in whatever context is appropriate)
   * FLFieldAction_GO         -Enter performs a "go" operation to take the user to the target of the text they typed. Typically used, for example, when entering a URL
   * FLFieldAction_NEXT       -Enter performs a "next" operation, taking the user to the next field that will accept text
   * FLFieldAction_SEND       -Enter performs a "send" operation, delivering the text to its target
   * FLFieldAction_NEW_LINE   -Enter performs a "new line" operation, taking the user cursor to the next line in the text field
   * FLFieldAction_DONE       -Enter performs a "done" operation, finishing user's input and usually hiding the virtual keyboard
   * FLFieldAction_EMOTICON   -Enter inserts :-) into text field
   *
   * Default: FLFieldAction_NEW_LINE
   */
  void setFieldAction(FLFieldAction fieldAction);
  
  FLFieldAction getFieldAction();
  
  /*
   * Sets manual punctuation mode(punctuation added from non QWERTY keyboard)
   * FLPunctuationSpaceMode_DEFAULT                [hello]+ -> [hello]+[.]-[|] Default behaviour doesn't eat or add space
   * FLPunctuationSpaceMode_DEL_PRECEEDING_SPACE   [hello]+ -> [hello]-[.]-[|] Eats space on previous word
   * FLPunctuationSpaceMode_ADD_SPACE_AFTER        [hello]+ -> [hello]+[.]+[|] Adds space after itself
   * FLPunctuationSpaceMode_DEL_AND_ADD_SPACE      [hello]+ -> [hello]-[.]+[|] Eats space on previous word AND adds space after itself
   *
   * Default: FLPunctuationSpaceMode_DEFAULT
   */
  void setPunctuationSpaceMode(FLPunctuationSpaceMode mode);
  
  /*
   * FLTextFieldType_REGULAR_TEXT   -Nothing special, regular text field
   * FLTextFieldType_PASSWORD       -Password field, Swipe up or down is disabled, suggestions are not displayed
   * FLTextFieldType_URL            -URL or Email field
   * FLTextFieldType_USER_AC_OFF    -User turned off AC. User still gets suggestions, and everything works as usual, except entered text is never automatically corrected
   *
   * Default: FLTextFieldType_REGULAR_TEXT
   */
  void setTextFieldType(FLTextFieldType type);
  
  /*
   * When platform detects long press, it can let engine know about it...
   *
   * FLLongPressType_NONE         -No longpress, can be used to reset the engine state
   * FLLongPressType_LONG_PRESS   -Long press. Next sendTap() will be treated as accurate typing. If x,y is valid, then sendTap() will return an accented character
   *
   * Optional: x,y - point where the long press was released. (this is not used at this moment)
   * 
   */
  void longPress(FLLongPressType type, float x = -1, float y = -1);
  
  /*
   * The exact character input of the user is respected more when blind mode is off. Eg. "in" will not be corrected to "on"
   *
   * Default: false
   */
  void setBlindMode(bool enabled);
  
  /*
   * Enable/Disable auto-learning.
   * Default: true
   */
  void setAutoLearning(bool isEabled);
  
  /*
   * SU becomes SD and SD becomes SU.
   */
  void setInvertSwipeUpAndDown(bool isInverted);
    
  FLUnicodeString getVersion();
  
  void setUseAllAccents(bool use);
  
  void setUseAppleSymbols(bool use);
  
  /*
   Sets the noise estimation state of the system keyboard for key distance average and
   std
   
   @param avg
   avg key distance 
   
   @param std
   spread of the key taps
   */
  void setKeyDistanceNE(float avg, float std);
  
  /*
   Sets the noise estimation state of the system keyboard for rotation estimation
   
   @param avg
   avg rotational changes
   
   @param std
   spread of the rotational changes
   */
  void setRotationNE(float avg, float std);

  /*
   Sets the noise estimation state of the system keyboard for scaling estimation
   
   @param avg
   avg scale change
   
   @param std
   spread of the scaling change
   */
  void setScalingNE(float avg, float std);
  
  /*
   Sets the noise estimation state of the system keyboard for key distance centered 
   about the tap center of mass
   
   @param avg
   NOT USED, so set to zero
   
   @param std
   spread of the rotational changes
   */
  void setKeyDistance2NE(float avg, float std);
  
  /*
   * Returns word "type". Type indicating if this word is in Dawg or was later added by the user
   * @param word
   * Word to search
   */
  FLDictionaryWordType getDictionaryWordType(FLUnicodeString word);
  
  /*
   * Experimental.
   * Locks and unlocks mmaped memory so that all of the jet file is loaded by the time user starts typing
   */
  bool warmUpJet();
  bool lockJetContents();
  bool unlockJetContents();
  
  /*
   As named.
   */
  bool doesLangUseCaps() const;
  
  /*
   As named.
   */
  int getNumShiftKeyboards() const;
  
  /*
   as named
   */
  bool getRightToLeft() const;
  
  /*
   as named
   */
  bool getTallCandies() const;
  
  /*
   * Sets if keyboard interaction events should be tracked. Events such as number of SR, SL, SU etc.
   * OFF by default
   */
  void setIsTracking(bool isTracking);
  
  /*
   * Sets if we're tracking all the user interactions, including taps, swipes, typing sessions etc.
   * OFF by default
   */
  void setIsCollectingData(bool isCollectingData);
  
  /*
   * Sets data file header in data collector
   */
  void setDataFileHeader(FLUnicodeString header);
  
  /*
   * Checks if language pack in resourceFilePath is valid
   */
  bool isValidLanguagePack(const char *resourceFilePath);
  
  /*
   * Gets array of words in temporary dictionary from auto-learning
   */
  std::vector<FLUnicodeString> getWordsInTemporaryDictionary();
  
  /*
   * Sets array of words in temporary dictionary for auto-learning
   */
  void setWordsInTemporaryDictionary(std::vector<FLUnicodeString> temp_words);
  
  
  //private:
  FleksyAPIpImpl *pImpl;
};

#endif /* defined(__FleksySDK_FleksyAPI_h__) */
