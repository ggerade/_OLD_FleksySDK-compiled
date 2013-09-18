//
//  FLConsistencyChecker.h
//  FleksyApiTest
//
//  Created by Vadim Maximov on 1/31/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FLCONSISTENCYCHECKER
#define FLCONSISTENCYCHECKER

#include <iostream>
#include "FleksyListenerInterface.h"
#include "FLTypingController.h"

class FLTypingController;

class FLConsistencyChecker{
  
public:
  FLConsistencyChecker(FleksyListenerInterface &listener, FLTypingController *tc);
  
  void checkTextForConsistencyAndUpdate(std::string caller);
  bool areSelectionPositionsValid(int oldSelStart, int oldSelEnd, int newSelStart, int newSelEnd);
  bool isTextBlockTextEqualsToScreenText(FLString screenText, std::string caller);
  /**checks if old text is still valid. if not reparses everything*/
  bool isTextStillValid(FLString text, int cursorPosition);
  void checkCursorPositionVSnumOfTextBlocks(int userCursorPosition, vector<FLTextBlock*> &textBlocks);
  void sendErrorReport(string message);
  
private:
  FleksyListenerInterface &out;
  FLTypingController *tc;
  
  void updateTextBlockCursor(int userCursorPosition = -1);
  
  
  
};

#endif
