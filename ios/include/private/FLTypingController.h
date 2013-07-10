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
#include "FLKeyMap.h"
#include "FLTextBlockCursor.h"
#include "SystemsIntegrator.h"
#include "FLConsistencyChecker.h"
#include "FLPlatformSuggestions.h"
#include "FLTrackEvents.h"
#include "FLDataCollector.h"

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
  void sendPoint(float x, float y, long long time);
  void backAndForthSwipe(float length = 0);
	void swipeRight(float length = 0);
	void swipeLeft(float length = 0);
	void swipeUp(float length = 0);
	void swipeDown(float length = 0);
  void enterSwipe(float length = 0);
  void shiftPressed(string who, bool userPress = false);
  void setActiveKeyboard(FLKeyboardID id, bool buttonPress);
  FLKeyboardID getActiveKeyboardID();
  void setCorrectionMode(FLCorrectionMode mode);
  FLCorrectionMode getCorrectionMode();
  void cursorSelectionChanged(int selectionStart, int selectionEnd);
  void startTypingSession(bool platformMovesCursor = false);
  void endTypingSession();
  void postLoadSetup();
  void setPlatformSuggestions(FLString prossedRequestID, FLString processedResults);
  void setCapitalizationMode(FLCapitalizationMode mode);
  FLCapitalizationMode getCapitalizationMode();
  void setVoiceFeedback(bool isOn);
  
  void setMaxNumberOfSuggestions(int numOfSuggestions); //Private API uses this
  std::string getVersionNumber(); //Version number of TC
  void setDeleteMode(FLDeleteMode mode);
  FLTrackEvents *getTracker();
  
  //Here for testing
  void sendCharacter(char c);//Testing sends character and this function coverts it into points and calls sendPoint()
  int getCursorPosition();//only used by TC tester
  FLString getTextFromTextBlocks();// in public for debugging
  bool getShiftState();//only used by TC tester
  //EOF testing functions

  //Crazy Cheker uses these
  FLTextBlockCursor * getTextBlockCursor();
  void setUserCursor(int userCursor, string caller);
  void resetIgnoreNextCursorUpdateCount();
  void underlineCurrentTextBlock();
  void previousWordChanged(string from, int textBlockInex = -1);
  void parseExistingText(FLString existingText = FLStringMake(""), int cursorPosition = -1);
  //EOF crazyChecker functions
  
  void setCurrentKeyboardLayout(string keyboardLayout);
  FLDataCollector *getDataCollector();

private:
  std::string lastBatchEditBeginFunction; // Debugging?

	FleksyListenerInterface &out;
	std::vector<FLString> punctuation;
	std::vector<FLTextBlock*> textBlocks;
  
  std::string versionNumber;
	int expectedUserCursor;//loaction of the cursor
  int userSelectionStart;
  int userSelectionEnd;
  
	int ignoreNextCursorUpdateCount;//how may cursor updates to ignore(by how much cursor has moved)
  int maxNumberOfSuggestions;
  bool isShiftPressed;
  bool simulateSystemCursorUpdates; //true = simulation of updates, false - updates come from the system
  bool isUserSelectedTB; //indicates if user selectedTB by moving the cursor
  FLCorrectionMode correctionMode;
  
  //TODO:rename this 
  bool isFirstInputAfterParsing;
  //////
  bool isEngineLoaded;
  bool voiceFeedback;
  bool startedTypingSession;
  bool inBatchEdit;
  FLCapitalizationMode capitalizationMode;
  CursorChangeEvent cursorChangeEvent;
  FLDeleteMode deleteMode;
  
  //Created in TC, so TC needs to destroy these
  FLTextBlockCursor *tbCursor = NULL;
  FLConsistencyChecker *crazyCheck = NULL;
  FLPlatformSuggestions *platformSuggestions = NULL;
  FLTrackEvents *tracker = NULL;
  FLDataCollector *dataCollector = NULL;
  //Just pointers
  SystemsIntegrator *fleksy = NULL;
  FLTextBlock *lastUpdatedTB = NULL;
  
  //Debug stuff
  void printTextBlocks();
  string getSlashSeparatedSuggestions(vector<FLString> suggestions);
  
  //Stuff that deletes
  void backspace();
  void deleteTextBlock();
  void deleteCharacterAt(int indx);
  void deleteCurrentTextBlock();
  int deleteAnySelectedText(FLExternalEditorState &state);
  
  //TextBlock correction operations
  FLString* getTwoPreviousTokens(int textBlockIndex);
  void getSuggestionsForTextBlock(FLTextBlock *tb, int textBlockIndex = -1);
  void handleVerticalSwipe(bool isUp);
  void correctTextBlockOnSwipeRight(FLTextBlock *tb);
  void correctTextBlockOnVerticalSwipe();
  int correctToNextSuggestion(FLTextBlock *tb, bool isUp);
  void changeTextBlockSuggestionWithCursorInTheMiddle(FLTextBlock *currTextBlock, int indxInTextBlock, bool isUp);
  
  //Various helper functioins
  FLChar getNearestChar(FLPoint p);
  std::vector<FLPoint> getPointsForText(FLString word);
  void reset();
  void createPunctuationSuggestions();
  void handleNonQWERTYCharacter(FLChar Character, FLPoint p);
  void ignoreNextCursorUpdate(std::string from, int num_ignores);
	void ignoredCursorUpdate(std::string from, int num_ignores);
  bool isInPunctuation(char symbol);
  bool isEndSentenceSymbol(char symbol);
  bool selectedTextAndConsistencyCheck(bool isVerticalSwipe = false);
  void addRemoveFromDictionary(FLTextBlock *tb);
  void GCtextBlocks();
  int calculateEndOfTextBlock(FLTextBlock *tb);
  void expectCursorUpdates(string from, int numOfUpdates);
  void apostropheSmergeCheck();
  void updateTBCursorAfterParsing(FLString blockText, FLExternalEditorState state);
  void getReadyForInput();
  void onBeginBatchEdit();
  void onEndBatchEdit();
  void batchEditCheck(int newSelStart, int newSelEnd);
  
  //User cursor operations
  void moveCursorToPosition(int position);
  int setSpaceFlagOnTextBlock(FLTextBlock * tb, bool isSpaceEnabled);
  void accountForLenghthDiffWhenCorrectingWords(int lengthDiff);
  void changeUserCursor(int byNumber, string caller);
  void incrementUserCursorBy(int number, string caller);
  void decrementUserCursorBy(int number, string caller);
  int getUserCursorPos();
  void setUserSelection(int selectionStart, int selectionEnd);
  void onUpdateSelection(int oldSelStart, int oldSelEnd, int newSelStart, int newSelEnd);
  
  //TextBlock operations
	int addTextBlock(FLTextBlock *block);
  FLTextBlock* createTextBlockFromExistingText(FLString &blockText);
	void addSymbolsTextBlock();
  void insertTextBlockInTextBlock(FLTextBlock *TBtoSplit, FLString TBtoInsertText, int indexInTB, int indexInVector);
  void createTextBlockFromExistingTextAndUpdateTBCursor(FLString blockText);
  void updateTextBlockCursorBasedOnCursorPosition(int cursorPosition = -1);
  void splitTextBlockWithSpace(FLTextBlock *TBtoSplit, int indxInTBtoSplitAt, int indxOfTBinVector);
  void mergeTextBlocks(FLTextBlock *tb1, FLTextBlock *tb2, int tb1Indx, int indxInTB);
  void mergeTextBlocksCheck();
  
  //UI&User Feedback
  void setComposingRegionForTextBlock(FLTextBlock* tb, int userCursor, bool isSpaceIncluded);
  void updateShiftState(bool forcedUpdate = false);
  void updateCandidatesView();
  void clearCandidatesView();
  void forceCandidateViewUpdate();
  void speak(FLString text, bool isDeleted);
  
  
  
};
#endif
