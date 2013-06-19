
#include "FLTypingControllerTestCase.h"

using namespace std;

FLTypingControllerTestCase::FLTypingControllerTestCase(FLTypingController &typingController, FleksyListenerImplC &outImpl, FleksyAPI *api) : tc(typingController), out(outImpl){
  testInfo = FLTestInfoPtr(new FLTestInfo(""));
  this->api = api;
}

FLTypingControllerTestCase::~FLTypingControllerTestCase(){
}
void FLTypingControllerTestCase::addAction(FLTypingControllerActionPtr &action){
  actions.push_back(action);
}
int FLTypingControllerTestCase::run(){
  tc.setCorrectionMode(FLCorrectionMode_ALWAYS);
  int result = 0;
  for(int i = 0; i < actions.size(); i++){
    result = performAction(actions[i]);
    if(result == 1){
      return result;
    }
  }
  return result;
}

int FLTypingControllerTestCase::performAction(FLTypingControllerActionPtr &action){
  string actionType = action->action;
  lastActionInfo = actionType;
  
  if(actionType == "SC"){
    tc.sendCharacter(action->character[0]);
    return checkSuggestion(action);
  }
  else if(actionType == "SR"){
    api->space(false);
    return checkSuggestion(action);
  }
  else if(actionType == "SL"){
    api->backspace(false);
    return checkSuggestion(action);
  }
  else if(actionType == "SD"){
    api->nextSuggestion();
    return checkSuggestion(action);
  }
  else if(actionType == "SU"){
    api->previousSuggestion();
    return checkSuggestion(action);
  }
  else if(actionType == "KB"){
    lastActionInfo.append(" " + to_string(action->keyboardNumber));
    api->setActiveKeyboard((FLKeyboardID)(action->keyboardNumber));
    return 0;
  }
  else if(actionType == "AC"){
    FLCorrectionMode mode;
    if(action->autoCorrect){
      mode = FLCorrectionMode_ALWAYS;
    }
    else{
      mode = FLCorrectionMode_OFF;
    }
    lastActionInfo.append(" FLCorrectionMode: " + to_string(mode));
    api->setCorrectionMode(mode);
    return 0;
  }
  else if(actionType == "SH"){
    api->toggleShift();
    return 0;
  }
  else if(actionType == "NL"){
    api->enter();
    return checkSuggestion(action);
  }
  else if(actionType == "MC"){
    int newCursorPos = 0;
    if(action->cursorPosRelation == 0){
      newCursorPos = action->cursorPosition;
    }
    else if(action->cursorPosRelation == 1){
      newCursorPos = tc.getCursorPosition() + action->cursorPosition;
    }
    else if(action->cursorPosRelation == -1){
      newCursorPos = tc.getCursorPosition() - action->cursorPosition;
    }
    lastActionInfo.append(" to: " + to_string(newCursorPos));
    out.onChangeSelection(newCursorPos, newCursorPos);
    api->cursorSelectionChanged(newCursorPos, newCursorPos);
    return checkSuggestion(action);
  }
  else if(actionType == "ST"){
    out.TESTsetScreenText(action->expectedOutput);
    api->startTypingSession();
    return 0;
  }
  else if(actionType == "MC end"){
    int newCursorPos = (int)tc.getTextFromTextBlocks().length();
    lastActionInfo.append(" to: " + to_string(newCursorPos));
     out.onChangeSelection(newCursorPos, newCursorPos);
     api->cursorSelectionChanged(newCursorPos, newCursorPos);
    return 0;
  }
  else if(actionType == "EC end"){
    action->cursorPosition = (int)tc.getTextFromTextBlocks().length();
    return checkCursorPosition(tc, action);
  }
  else if(actionType == "ET"){
    return checkText(tc, action);
  }
  else if(actionType == "EC"){
    return checkCursorPosition(tc, action);
  }
  else if(actionType == "EOT"){
    printf("\n--------%s: PASSED ALL TESTS -------------\n", this->testInfo->testName.c_str());
    return 0;
  }
  else if(actionType == "BF"){
    api->backspace(true);
    return checkSuggestion(action);
  }
  else if(actionType == "SHC"){
    return checkShiftState(action);
  }
  else if(actionType == "TBC"){
    FLTextBlockCursor *tbCursor = tc.getTextBlockCursor();
    return checkTextBlockCursor(tbCursor, action);
  }
  else if (actionType == "SEL"){
    lastActionInfo.append(" start: " + to_string(action->selectionStart) + " end: " + to_string(action->selectionEnd));
    api->cursorSelectionChanged(action->selectionStart, action->selectionEnd);
    out.onChangeSelection(action->selectionStart, action->selectionEnd);
    return checkCursorSelection(action);
  }
  else if(actionType == "EUL"){
    return checkComposingRegion(action);
  }
  else if(actionType == "CAPS"){
    FLCapitalizationMode mode;
    if(action->isUpperCase){
      mode = FLCapitalizationMode_CAP_ALL;
    }
    else{
      mode = FLCapitalizationMode_CAP_SENTENCES;
    }
    lastActionInfo.append(" FLCapitalizationMode: " + to_string(mode));
    api->setCapitalizationMode(mode);
    return 0;
  }
  else{
    LOGI("Unknown Action: %s", actionType.c_str());
    return 1;
  }
}

string FLTypingControllerTestCase::getLastActionInfo(){
  return lastActionInfo;
}

int FLTypingControllerTestCase::checkText(FLTypingController &tc, FLTypingControllerActionPtr &action){
  CheckType checkType;
  checkType.type = "ET";
  if(out.getTextOnScreen() == action->expectedOutput){
    printf("\n--------%s: TEXT PASS", this->testInfo->testName.c_str());
    printf("----------\n\n");
    checkType.result = "Expected Text=PASS ";
    checkType.result.append("(");
    checkType.result.append(action->expectedOutput);
    checkType.result.append(")");
    testInfo->addCheckType(checkType);
    
    return 0;
  }
  printf("\n--------%s: TEXT FAIL>", this->testInfo->testName.c_str());
  printf("Text doesnt match! Expected:<%s> got:<%s>", action->expectedOutput.c_str(), out.getTextOnScreen().c_str());
  printf("----------\n\n");
  checkType.result = string("Expected Text=FAIL: ") + "Text doesnt match! Expected: <" + action->expectedOutput.c_str() + "> got <" +  out.getTextOnScreen().c_str() + ">";
  testInfo->addCheckType(checkType);
  return 1;
}

int FLTypingControllerTestCase::checkCursorPosition(FLTypingController &tc, FLTypingControllerActionPtr &action){
  CheckType checkType;
  checkType.type = "EC";
  if(action->cursorPosition == tc.getCursorPosition()){
    printf("\n--------%s: CURSOR POSITION PASS", this->testInfo->testName.c_str());
    printf("----------\n\n");
    checkType.result = "Expected Cursor Position=PASS";
    checkType.result.append("(");
    checkType.result.append(to_string(action->cursorPosition));
    checkType.result.append(")");
    
    testInfo->addCheckType(checkType);
    return 0;
  }
  printf("\n--------%s: CURSOR POSITION FAIL>", this->testInfo->testName.c_str());
  printf("Expected Cursor position doesnt match! Expected: %i got: %i", action->cursorPosition, tc.getCursorPosition());
  printf("----------\n\n");
  checkType.result = "Cursor Position=FAIL: Cursor position doesnt match! Expected: ";
  checkType.result.append(to_string(action->cursorPosition));
  checkType.result.append(" got: ");
  checkType.result.append(" " + to_string(tc.getCursorPosition()));
  testInfo->addCheckType(checkType);
  return 1;
}

int FLTypingControllerTestCase::checkTextBlockCursor(FLTextBlockCursor *tbCursor, FLTypingControllerActionPtr &action){
  CheckType checkType;
  checkType.type = "TBC";
  if(action->blockIndex == tbCursor->getIndexOfCurrentTextBlockInVector() && action->indexInBlock == tbCursor->getIndexInTextBlock()){
    printf("\n--------%s: TEXTBLOCKCURSOR PASS (%i,%i)", this->testInfo->testName.c_str(), action->blockIndex, action->indexInBlock);
    printf("----------\n\n");
    checkType.result = "TBCursor=PASS";
    checkType.result.append("(");
    checkType.result.append(to_string(action->blockIndex));
    checkType.result.append(",");
    checkType.result.append(to_string(action->indexInBlock));
    checkType.result.append(")");
    testInfo->addCheckType(checkType);
    return 0;
  }
  printf("\n--------%s: TEXTBLOCKCURSOR FAIL>", this->testInfo->testName.c_str());
  printf("Expected blockIndex: %i got: %i,  Expected indexInBlock: %i got: %i>", action->blockIndex, tbCursor->getIndexOfCurrentTextBlockInVector(), action->indexInBlock, tbCursor->getIndexInTextBlock());
  printf("----------\n\n");
  checkType.result = "TEXTBLOCKCURSOR FAIL:";
  checkType.result.append(" Expected blockIndex: " + to_string(action->blockIndex));
  checkType.result.append(" got: " + to_string(tbCursor->getIndexOfCurrentTextBlockInVector()));
  checkType.result.append(", Expected indexInBlock: " + to_string(action->indexInBlock));
  checkType.result.append(" got: " + to_string(tbCursor->getIndexInTextBlock()));
  testInfo->addCheckType(checkType);
  return 1;
}

string FLTypingControllerTestCase::getStringForBoolean(bool b){
  return (b)?"true":"false";
}

int FLTypingControllerTestCase::checkShiftState(FLTypingControllerActionPtr &action){
  CheckType checkType;
  checkType.type = "SH";
  if(action->expectedShiftState == tc.getShiftState()){
    printf("\n--------%s: SHIFTSTATECHECK PASS", this->testInfo->testName.c_str());
    printf("----------\n\n");
    checkType.result = "SHIFTSTATECHECK=PASS";
    testInfo->addCheckType(checkType);
    return 0;
  }
  printf("\n--------%s: SHIFTSTATECHECK FAIL: ", this->testInfo->testName.c_str());
  printf("Expected shift state to be <%s>, got <%s>", getStringForBoolean(action->expectedShiftState).c_str(), getStringForBoolean(tc.getShiftState()).c_str());
  printf("----------\n\n");
  checkType.result = "SHIFTSTATECHECK FAIL:";
  checkType.result.append(" Expected shift state to be <" + getStringForBoolean(action->expectedShiftState) + ">");
  checkType.result.append(" got <" + getStringForBoolean(tc.getShiftState()) + ">");
  testInfo->addCheckType(checkType);
  return 1;
}

int FLTypingControllerTestCase::checkComposingRegion(FLTypingControllerActionPtr &action){
  int start = out.getComposingStart();
  int end = out.getComposingEnd();
  CheckType checkType;
  checkType.type = "EUL";
  if(action->composingStart == start && action->composingEnd == end){
    printf("\n--------%s: UNDLERLINE PASS (composingStart: %i, composingEnd: %i)", this->testInfo->testName.c_str(), action->composingStart, action->composingEnd);
    printf("----------\n\n");
    checkType.result = "ComposingRegion=PASS";
    checkType.result.append("(");
    checkType.result.append(to_string(action->composingStart));
    checkType.result.append(",");
    checkType.result.append(to_string(action->composingEnd));
    checkType.result.append(")");
    testInfo->addCheckType(checkType);
    return 0;
  }
  printf("\n--------%s: UNDLERLINE FAIL>", this->testInfo->testName.c_str());
  printf("Expected composingStart: %i got: %i,  Expected composingEnd: %i got: %i>", action->composingStart, start, action->composingEnd, end);
  printf("----------\n\n");
  checkType.result = "ComposingRegion FAIL:";
  checkType.result.append(" Expected composingStart: " + to_string(action->composingStart));
  checkType.result.append(" got: " + to_string(start));
  checkType.result.append(", Expected composingEnd: " + to_string(action->composingEnd));
  checkType.result.append(" got: " + to_string(end));
  testInfo->addCheckType(checkType);
  return 1;
}

int FLTypingControllerTestCase::checkCursorSelection(FLTypingControllerActionPtr &action){
  int start = out.getSelectionStart();
  int end = out.getSelectionEnd();
  CheckType checkType;
  checkType.type = "SEL";
  if(action->selectionStart == start && action->selectionEnd == end){
    printf("\n--------%s: SELECTION PASS (selectionStart: %i, selectionEnd: %i)", this->testInfo->testName.c_str(), action->selectionStart, action->selectionEnd);
    printf("----------\n\n");
    checkType.result = "CursorSelection=PASS";
    checkType.result.append("(");
    checkType.result.append(to_string(action->selectionStart));
    checkType.result.append(",");
    checkType.result.append(to_string(action->selectionEnd));
    checkType.result.append(")");
    testInfo->addCheckType(checkType);
    return 0;
  }
  printf("\n--------%s: SELECTION FAIL>", this->testInfo->testName.c_str());
  printf("Expected composingStart: %i got: %i,  Expected composingEnd: %i got: %i>", action->selectionStart, start, action->selectionEnd, end);
  printf("----------\n\n");
  checkType.result = "CursorSelection FAIL:";
  checkType.result.append(" Expected selectionStart: " + to_string(action->selectionStart));
  checkType.result.append(" got: " + to_string(start));
  checkType.result.append(", Expected selectionEnd: " + to_string(action->selectionEnd));
  checkType.result.append(" got: " + to_string(end));
  testInfo->addCheckType(checkType);
  return 1;
}

int FLTypingControllerTestCase::checkSuggestion(FLTypingControllerActionPtr &action){
  if(action->suggestionIndex == -1){return 0;}
  CheckType checkType;
  checkType.type = "Suggestion Check";
  if(action->suggestionIndex == out.getSuggestionIndex()){
    printf("\n--------%s: Suggestion Index Check PASSED (SuggestionIndex: %i)", this->testInfo->testName.c_str(), action->suggestionIndex);
    printf("----------\n\n");
    checkType.result = "SuggestionIndex=PASS";
    checkType.result.append("(");
    checkType.result.append(to_string(action->suggestionIndex));
    checkType.result.append(")");
    
    string suggestion((char*)out.getSuggestionForIndex(action->suggestionIndex).c_str());
    string textAroundCursor((char*)out.getTextAroundCursor((int)suggestion.length()).c_str());
    transform(suggestion.begin(), suggestion.end(), suggestion.begin(), ::tolower);
    transform(textAroundCursor.begin(), textAroundCursor.end(), textAroundCursor.begin(), ::tolower);
    
    if(textAroundCursor.find(suggestion) != string::npos){
      printf("\n--------%s: Suggestion Match PASSED (Suggestion: <%s>)", this->testInfo->testName.c_str(), suggestion.c_str());
      printf("----------\n\n");
      checkType.result.append(", Suggestion Match PASSED (Suggestion: <");
      checkType.result.append(suggestion);
      checkType.result.append(">)");
      testInfo->addCheckType(checkType);
      return 0;
    }
    printf("\n--------%s: Suggestion Match FAILED (Suggestion: <%s> is not found in text: <%s>)", this->testInfo->testName.c_str(), suggestion.c_str(), textAroundCursor.c_str());
    printf("----------\n\n");
    checkType.result.append(", SuggestionMatch=FAIL Suggestion: <");
    checkType.result.append(suggestion);
    checkType.result.append("> is not found in text: <");
    checkType.result.append(textAroundCursor);
    checkType.result.append(">");
    testInfo->addCheckType(checkType);
    return 1;
  }
  printf("\n--------%s: Suggestion Index Check FAILED (Expected: %i got: %i)", this->testInfo->testName.c_str(), action->suggestionIndex, out.getSuggestionIndex());
  printf("----------\n\n");
  checkType.result = "Suggestion Index doesn't match! Expected: ";
  checkType.result.append(to_string(action->suggestionIndex));
  checkType.result.append(" got: ");
  checkType.result.append(to_string(out.getSuggestionIndex()));
  testInfo->addCheckType(checkType);
  return 1;
}





