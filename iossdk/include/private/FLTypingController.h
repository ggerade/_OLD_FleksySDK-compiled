#ifndef FLTYPINGCONTROLLER_H
#define FLTYPINGCONTROLLER_H

#include <vector>
#include <string>
#include <map>
#include "FLTouchPoint.h"
#include "FLTextBlock.h"
#include "FLRequestDataHolder.h"
#include "PatternRecognizer/Platform.h"
#include "FleksyListenerInterface.h"
#include "FLTextBlockCursor.h"
#include "SystemsIntegrator.h"
#include "FLConsistencyChecker.h"
#include "FLTrackEvents.h"
#include "FLDataCollector.h"
#include "FLUnicodeString.h"
#include "FLAutoLearn.h"

class FLConsistencyChecker;

struct CursorChangeEvent{
  bool useThisEvent = false;
  int newSelStart = 0;
  int newSelEnd = 0;
};

class FLTypingController{
  
public:
	FLTypingController(FleksyListenerInterface &listener, SystemsIntegrator* fleksy);
  ~FLTypingController();
  
  //FleksyAPI calls
  void sendPoint(float x, float y, long long time, int offset, FLUnicodeString character);
  void backAndForthSwipe(float length = 0);
	void swipeRight(const FLUnicodeString& hint, float length = 0);
	void swipeLeft(float length = 0);
	int swipeUp(float length = 0);
	int swipeDown(float length = 0);
  void enterSwipe(float length = 0);
  void shiftPressed(const std::string &who, bool userPress = false);
  void setActiveKeyboard(FLKeyboardID id, bool buttonPress);
  FLKeyboardID getActiveKeyboardID();
  void setCorrectionMode(FLCorrectionMode mode);
  FLCorrectionMode getCorrectionMode();
  void cursorSelectionChanged(int selectionStart, int selectionEnd);
  void startTypingSessionWithExtra(bool platformMovesCursor, FLFieldAction fieldAction, FLKeyboardSize keyboardSize, FLKeyboardLayout layout, FLKeyboardAlpha alphaState);
  void endTypingSession();
  void postLoadSetup();
  void setCapitalizationMode(FLCapitalizationMode mode);
  FLCapitalizationMode getCapitalizationMode();
  void setVoiceFeedback(bool isOn);
  void setDeleteMode(FLDeleteMode mode);
  void setFieldAction(FLFieldAction fieldAction);
  void setPunctuationSpaceMode(FLPunctuationSpaceMode mode);
  void setTextFieldType(FLTextFieldType type);
  void longPress(FLLongPressType type, float x, float y);
  bool isShifted();
  FLFieldAction getCurrentFieldAction();
  void setInvertedVerticalSwipe(bool isInverted);
  bool isVerticalSwipeInverted();
  void setAutoLeaning(bool isEnabled);
  
  void setMaxNumberOfSuggestions(int numOfSuggestions); //Private API uses this
  FLUnicodeString getVersionNumber(); //Version number of TC
  
  
  //Here for testing
  void sendCharacter(const FLUnicodeString &c, bool usePassedChar = false);//Testing sends character and this function coverts it into points and calls sendPoint()
  int getCursorPosition();//only used by TC tester
  FLUnicodeString getTextFromTextBlocks();// in public for debugging
  bool getShiftState();//only used by TC tester
  FLUnicodeString getTCDebugInfo();
  FLTextBlock* getTextBlockAt(int index);
  
  // Two sets of tokens, first plain, second marking if the tokens were user typed words.
  std::pair<std::vector<FLUnicodeString>, std::vector<FLUnicodeString>> getTwoPreviousTokens(int textBlockIndex);
  //EOF testing functions

  //Crazy Cheker uses these
  FLTextBlockCursor * getTextBlockCursor();
  void setUserCursor(int userCursor, const std::string &caller);
  void resetIgnoreNextCursorUpdateCount();
  void underlineCurrentTextBlock(bool justBackspaced = false);
  void parseExistingText(const FLUnicodeString &existingText = FLUnicodeString((const unsigned char *)""), int cursorPosition = -1, bool deletedSelectedText = false);
  int getUserCursorPos();
  //EOF crazyChecker functions
  
  void setCurrentKeyboardLayout(const std::string &keyboardLayout);
  FLDataCollector *getDataCollector();
  
  //Autolearning
  std::vector<FLUnicodeString> getWordsInTemporaryDictionary();
  void setWordsInTemporaryDictionary(std::vector<FLUnicodeString> temp_words);
  
  void enableGoatMode();
  
  // Debug
  FLUnicodeString displayString(bool withPoints = false, bool printDirectly = false);
  void printTextBlocks(bool withPoints = false);
  void printfTextBlocks(bool withPoints = false);
  
  // PUBLIC for data extractor
  void setUpdateNoiseEstimation(bool value);
  bool getUpdateNoiseEstimation(void);
  
  // For data extractor.
  std::vector<FLTextBlock*> getTextBlocks() { return textBlocks; }
  bool updateTextBlockSuggestions(FLTextBlock *tb, std::vector<FLUnicodeString> suggs);
  FLTextBlock* findTBMatchingSuggestions(const std::vector<FLUnicodeString> &suggs);
  void testTBIntegrity() const;
  FLTextFieldType getTextFieldType() const { return textFieldType; }
  FLCorrectionMode getCorrectionMode() const { return correctionMode; }
  void testOnlyDoFakeCorrections(bool doThem) { _doFakeCorrections = doThem; }
  void testOnlySetOldSchoolSplittage(bool old) { _oldSchoolSplittage = old; }
  bool testOnlyJustDeletedTB() { return _justDeletedTB; }
  void testOnlyResetJustDeletedTB() { _justDeletedTB = false; }
  bool testOnlyJustSplitWithSpace() { return _justSplitWithSpace; }
  void testOnlyResetJustSplitWithSpace() { _justSplitWithSpace = false; }

private:
  void batchEditWithBlock(const char* funcName, std::function<void(void)> func);
  
  std::string lastBatchEditBeginFunction; // Debugging?

	FleksyListenerInterface &out;
	std::vector<FLUnicodeString> punctuation;
  std::vector<FLUnicodeString> specialCases;
  std::vector<FLUnicodeString> emoticons;
	std::vector<FLTextBlock*> textBlocks;
  std::map<FLUnicodeString, FLUnicodeString> wordToEmoji;
  
  FLUnicodeString versionNumber;
	int expectedUserCursor;//loaction of the cursor
  int userSelectionStart;
  int userSelectionEnd;
  
  int gameKeyChargingOffset;
  
	int ignoreNextCursorUpdateCount;//how may cursor updates to ignore(by how much cursor has moved)
  double lastCursorUpdateMatched;
  
  int maxNumberOfSuggestions;
  bool isShiftPressed;
  bool simulateSystemCursorUpdates; //true = simulation of updates, false - updates come from the system
  bool isUserSelectedTB; //indicates if user selectedTB by moving the cursor
  FLCorrectionMode correctionMode;
  
  //TODO:rename this 
  bool isFirstInputAfterParsing;
  //////
  bool areSwipesInverted;
  bool isUserShifting;
  bool isEngineLoaded;
  bool voiceFeedback;
  bool startedTypingSession = false;
  bool inBatchEdit;
  bool goatMode;
  bool _updateNoiseEstimation = true;
  
  // Values used by Data Explorer
  bool _oldSchoolSplittage = false;
  bool _justDeletedTB = false;
  bool _justSplitWithSpace = false;

  CursorChangeEvent cursorChangeEvent;
  
  FLCapitalizationMode capitalizationMode;
  FLDeleteMode deleteMode;
  FLFieldAction fieldAction;
  FLPunctuationSpaceMode punctuationSpaceMode;
  FLTextFieldType textFieldType;
  FLLongPressType longPressType;
  FLMessageType spaceBarState;
  
  FLUnicodeString lastDeletedRawText;
  FLUnicodeString lastDeletedCorrectedWord;
  
  FLUnicodeString gameText;
  double lastTapTime;
  
  //Created in TC, so TC needs to destroy these
  FLTextBlockCursor *tbCursor = NULL;
  FLConsistencyChecker *crazyCheck = NULL;
  FLDataCollector *dataCollector = NULL;
  FLAutoLearn *autoLearner = NULL;
  
  //Just pointers
  SystemsIntegrator *fleksy = NULL;
  FLTextBlock *lastUpdatedTB = NULL;
  
  //Debug stuff
  bool _doFakeCorrections = false;
  FLUnicodeString getDelimitedSuggestions(const std::vector<FLUnicodeString> &suggestions, FLUnicodeString originalWord, bool isWord);
  
  //Game key charging
  FLUnicodeString getIntendedCharacter(int offset);
  
  void startTypingSession(bool platformMovesCursor = false);
  
  // Utility functions
  std::pair<int, int> getSelectionRegion();
  std::pair<int, int> regionForTB(FLTextBlock *tb, bool includeSpace);
  
  //Stuff that deletes
  void backspace(float length);
  void deleteTextBlock();
  void deleteCharacterAt(int indx);
  void deleteCurrentTextBlock();
  int deleteAnySelectedText(FLExternalEditorState &state, bool isDeleting = false);
  
  //TextBlock correction operations
  void getSuggestionsForTextBlock(FLTextBlock *tb, int textBlockIndex = -1);
  int handleVerticalSwipe(bool isUp);
  void correctTextBlockOnSwipeRight(FLTextBlock *tb);
  void correctTextBlockOnVerticalSwipe();
  void correctToNextSuggestion(FLTextBlock *tb, bool isUp);
  void changeTextBlockSuggestionWithCursorInTheMiddle(FLTextBlock *currTextBlock, int indxInTextBlock, bool isUp);
  void createEmoticonTextBlock();
  void setPunctuationSuggestions(FLTextBlock *tb);
  void changeSuggestion(FLTextBlock *tb, int offset);
  void correctEnteredText(FLTextBlock *tb, bool isSpaceAfter);
  void prepareTextBlockToRecieveOrRemoveCharacters(FLTextBlock *tb);
  
  //Various helper functioins
  int measureTBLengthDiff(FLTextBlock *tb, std::function<void(void)> f);
  FLUnicodeString getNearestChar(FLPoint p);
  std::vector<FLPoint> getPointsForText(const FLUnicodeString &word);
  void reset();
  void GCtextBlocks();

  void populateSpecialVectors();

  void ignoreNextCursorUpdate(const std::string &from, int num_ignores);
  void expectCursorUpdates(const std::string &from, int numOfUpdates);

  void onBeginBatchEdit();
  void onEndBatchEdit();
  void batchEditCheck(int newSelStart, int newSelEnd);

  void handleNonQWERTYCharacter(const FLUnicodeString &Character, FLPoint p);
  FLUnicodeString toLowerCase(const FLUnicodeString &word);

  bool selectedTextAndConsistencyCheck(bool isVerticalSwipe = false, bool isDeleting = false);
  void addRemoveFromDictionary(FLTextBlock *tb);
  void updateTBCursorAfterParsing(FLUnicodeString &blockText, FLExternalEditorState state);
  void getReadyForInput();
  void closeComposingRegionAt(int position);
  double getUpdateTimeDiff();
  FLUnicodeString getGameCharacter(int index);
  std::vector<FLPoint> getSubVector(const std::vector<FLPoint> &original, int start, int end);
  void resetLongPressType();
  int getNumberOfQuotes();
  
  void apostropheSmergeCheck();

  bool canEatSpace(const FLUnicodeString &c);
  bool canAddSpace(const FLUnicodeString &c, FLTextBlock *prevTB);
  bool canAddSpaceAfterEating(const FLUnicodeString &c);
  bool canAddSymbolToTextBlock(const FLUnicodeString &character, const FLUnicodeString &blockText);

  bool isSymbolAllowedToCorrect(const FLUnicodeString &character);

  bool isInPunctuation(const FLUnicodeString &symbol);

  int calculateEndOfTextBlock(FLTextBlock *tb);
  void setLastDeletedWord(FLTextBlock *tb);
  
  //User cursor operations
  void moveCursorToPosition(int position);
  int setSpaceFlagOnTextBlock(FLTextBlock * tb, bool isSpaceEnabled);
  void accountForLenghthDiffWhenCorrectingWords(int lengthDiff);
  void changeUserCursor(int byNumber, const std::string &caller);
  void incrementUserCursorBy(int number, const std::string &caller);
  void decrementUserCursorBy(int number, const std::string &caller);
  void setUserSelection(int selectionStart, int selectionEnd);
  
  //TextBlock operations
	int addTextBlock(FLTextBlock *block);
  FLTextBlock* createTextBlockFromExistingText(FLUnicodeString &blockText);
	void addSymbolsTextBlock(bool keepSpaceOnCurrTB);
  void createTextBlockFromExistingTextAndUpdateTBCursor(FLUnicodeString &blockText);
  void updateTextBlockCursorBasedOnCursorPosition(int cursorPosition = -1);
  void splitTextBlockWithSpace(FLTextBlock *TBtoSplit, int indxInTBtoSplitAt, int indxOfTBinVector);
  void mergeTextBlocks(FLTextBlock *tb1, FLTextBlock *tb2, int tb1Indx, int indxInTB);
  bool mergeTextBlocksCheck();
  void checkTextBlockForSplittage(int indexOfTB);
  void convertToRegularTextBlock(FLTextBlock *tb);
  
  //UI&User Feedback
  void setComposingRegionForTextBlock(const FLTextBlock* tb, int userCursor, bool isSpaceIncluded);
  void updateShiftState(bool forcedUpdate = false);
  void updateCandidatesView(FLTextBlock *tbToUpdate = NULL);
  void clearCandidatesView();
  void forceCandidateViewUpdate(FLTextBlock *tbToUpdate = NULL);
  void speak(FLUnicodeString text, bool isDeleted);
  void speak(const FLTextBlock *tb, bool isDeleted, bool forceSpeak = false);
  FLMessageType getSpaceBarState();
  void sendSpacebarState(bool forceSend = false);
  
  void insertEmojiForWord(FLUnicodeString word, std::vector<FLUnicodeString> & suggestions);
  FLUnicodeString getTextBlockInfos();
};

#endif
