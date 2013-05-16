#ifndef __FleksyApiTest__FLTypingControllerTestCase__
#define __FleksyApiTest__FLTypingControllerTestCase__

#include <iostream>
#include "FLTypingController.h"
#include "FleksyPrivateAPI.h"
#include "FLTypingControllerAction.h"
#include "FleksyListenerImplC.h"
#include "FLTestInfo.h"

class FLTypingControllerTestCase{
  
public:
  
  
  FLTypingControllerTestCase(FLTypingController &typingController, FleksyListenerImplC &outImpl);
  ~FLTypingControllerTestCase();
  
  FLTypingController &tc;
  FleksyListenerImplC &out;
  
  FLTestInfo *testInfo;
  
  std::vector<FLTypingControllerAction*> actions;
  
  void addAction(FLTypingControllerAction *action);
  int run();
  
private:

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
