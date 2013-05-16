#ifndef __FleksyApiTest__FLTypingControllerTestCase__
#define __FleksyApiTest__FLTypingControllerTestCase__

#include <iostream>
#include "FLTypingController.h"
#include "FleksyPrivateAPI.h"
#include "FleksyListenerImplC.h"
#include "FLTestInfo.h"
#include "FleksyAPI.h"

struct FLTypingControllerAction{
  std::string action; //send character(SC), SR, SL, SU, SD, MC
  bool isUpperCase = false;
  int cursorPosition; // used if action is MC = moved cursor or O = expected output
  int keyboardNumber;
  std::string character; //used if action is send character
  std::string expectedOutput; // used if action is check O.
  int cursorPosRelation; //-1 = -, 1 = +, 0 = exact position
  int blockIndex;
  int indexInBlock;
  int composingStart;
  int composingEnd;
  int selectionStart;
  int selectionEnd;
  int suggestionIndex = -1;
  
  bool expectedShiftState; //true = on, false = off
  int onUpdateSelectionVals[4] = {0, 0, 0, 0};
  bool autoCorrect;
};

class FLTypingControllerTestCase{
  
public:
  
  
  FLTypingControllerTestCase(FLTypingController &typingController, FleksyListenerImplC &outImpl, FleksyAPI *api);
  ~FLTypingControllerTestCase();
  
  FLTypingController &tc;
  FleksyListenerImplC &out;
  FleksyAPI *api;
  
  FLTestInfo *testInfo;
  
  std::vector<FLTypingControllerAction*> actions;
  
  void addAction(FLTypingControllerAction *action);
  
  std::string getLastActionInfo();
  
  int run();
  
private:
  
  std::string lastActionInfo;

  int performAction(FLTypingControllerAction *action);
  int checkText(FLTypingController &tc, FLTypingControllerAction *action);
  int checkCursorPosition(FLTypingController &tc, FLTypingControllerAction *action);
  int checkTextBlockCursor(FLTextBlockCursor *TBcursor, FLTypingControllerAction *action);
  int checkShiftState(FLTypingControllerAction *action);
  int checkComposingRegion(FLTypingControllerAction *action);
  int checkSuggestion(FLTypingControllerAction *action);
  int checkCursorSelection(FLTypingControllerAction *action);
  
  
  std::string getStringForBoolean(bool b);
};

#endif /* defined(__FleksyApiTest__FLTypingControllerTestCase__) */
