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
#include "FLUnicodeString.h"


class FLTypingController;

class FLConsistencyChecker{
  
public:
  FLConsistencyChecker(FleksyListenerInterface &listener, FLTypingController *tc);
  
  void checkTextForConsistencyAndUpdate(const std::string &caller);
  bool areSelectionPositionsValid(int oldSelStart, int oldSelEnd, int newSelStart, int newSelEnd);
  bool isTextBlockTextEqualsToScreenText(const FLUnicodeString &screenText, const std::string &caller);
  /**checks if old text is still valid. if not reparses everything*/
  bool isTextStillValid(const FLUnicodeString &text, const std::vector<FLTextBlock*> *textBlocks, FLTextBlockCursor *tbCursor);
  void checkCursorPositionVSnumOfTextBlocks(int userCursorPosition, const std::vector<FLTextBlock*> &textBlocks);
  void sendErrorReport(const FLUnicodeString &message);
  
private:
  FleksyListenerInterface &out;
  FLTypingController *tc;
};

#endif
