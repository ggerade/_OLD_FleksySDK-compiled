#ifndef __FleksyApiTest__FLTypingControllerTestCase__
#define __FleksyApiTest__FLTypingControllerTestCase__

#include <iostream>
#include <memory>
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

typedef std::shared_ptr<FLTypingControllerAction> FLTypingControllerActionPtr;

class FLTypingControllerTestCase{
  
public:
  
  
  FLTypingControllerTestCase(FLTypingController &typingController, FleksyListenerImplC &outImpl, FleksyAPI *api);
  ~FLTypingControllerTestCase();
  
  FLTypingController &tc;
  FleksyListenerImplC &out;
  FleksyAPI *api;
  
  FLTestInfoPtr testInfo;
  
  std::vector<FLTypingControllerActionPtr> actions;
  
  void addAction(FLTypingControllerActionPtr &action);
  
  std::string getLastActionInfo();
  
  int run();
  
private:
  
  std::string lastActionInfo;

  int performAction(FLTypingControllerActionPtr &action);
  int checkText(FLTypingController &tc, FLTypingControllerActionPtr &action);
  int checkCursorPosition(FLTypingController &tc, FLTypingControllerActionPtr &action);
  int checkTextBlockCursor(FLTextBlockCursor *TBcursor, FLTypingControllerActionPtr &action);
  int checkShiftState(FLTypingControllerActionPtr &action);
  int checkComposingRegion(FLTypingControllerActionPtr &action);
  int checkSuggestion(FLTypingControllerActionPtr &action);
  int checkCursorSelection(FLTypingControllerActionPtr &action);
  
  
  std::string getStringForBoolean(bool b);
};

typedef std::shared_ptr<FLTypingControllerTestCase> FLTypingControllerTestCasePtr;

#endif /* defined(__FleksyApiTest__FLTypingControllerTestCase__) */
