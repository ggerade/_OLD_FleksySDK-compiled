//
//  FLTypingControllerTester.cpp
//  FleksyApiTest
//
//  Created by Vadim Maximov on 2/4/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#include "FLTypingControllerTester.h"
#include "VariousUtilities2.h"
#include "TimeFunctions.h"


FLTypingControllerTester::FLTypingControllerTester(char *executableResourcesPath){
  executableResourcesPathString = dirname(executableResourcesPath);
  fleksyListener = new FleksyListenerImplC();
  api = new FleksyAPI(*fleksyListener);
  tc = api->pImpl->tc;
}

FLTypingControllerTester::~FLTypingControllerTester(){
  delete fleksyListener;
  delete api;
  deleteTestInfos();
}

void FLTypingControllerTester::deleteTestInfos(){
  for(FLTestInfo *tI : testInfos){
    delete tI;
  }
  testInfos.clear();
}

void FLTypingControllerTester::createAction(string line, FLTypingControllerAction *a){
  FLTypingControllerAction *action = a;
  if(a == NULL){
   action = new FLTypingControllerAction();
  }
  action->suggestionIndex = -1;
  if(string::npos != line.find_first_of("(")){
    int paren1Indx = (int)line.find_first_of("(") + 1;
    action->action = line.substr(0, paren1Indx - 1);
    int paren2Indx = (int)line.find_first_of(")");
    string suggIndex = line.substr(paren1Indx, paren2Indx - paren1Indx);
    action->suggestionIndex = atoi(suggIndex.c_str());
  }
  else{
    action->action = line;
  }
  //printf("Action: %s\n", action->action.c_str());
  getLastTestCase()->addAction(action);
}

FLTypingControllerTestCase * FLTypingControllerTester::getLastTestCase(){
  return testCases[testCases.size() - 1];
}

void FLTypingControllerTester::deleteDataFromPreviousTest(FLTypingController &tc){
  LOGI("--DELETING OLD DATA...");
  int newPos = (int)tc.getTextFromTextBlocks().length();
  fleksyListener->onChangeSelection(newPos, newPos);
  tc.cursorSelectionChanged(newPos, newPos);
  
  while(tc.getTextFromTextBlocks().length() > 0){
    tc.swipeLeft();
  }
  tc.setActiveKeyboard(FLKeyboardID_QWERTY_UPPER);
  tc.setCapitalizationMode(FLCapitalizationMode_CAP_SENTENCES);
  LOGI("--FINISHED DELETING OLD DATA");
}

void FLTypingControllerTester::createFLTypingControllerTestCases(){
  
  char testCasesPath[PATH_MAX];
  snprintf(testCasesPath, sizeof(testCasesPath), "%s/typingControllerTestCases", executableResourcesPathString.c_str());

  ifstream fin;
  fin.open(testCasesPath);
  if (!fin.good()){
    char errorMessage[1024 + PATH_MAX];
    snprintf(errorMessage, sizeof(errorMessage), "Unable to open file: '%s'", testCasesPath);
    throw std::runtime_error(errorMessage);
  }
  else{
    printf("Test File found\n");
  }
  
  string line;
  
  while (!fin.eof()){
    
    getline(fin, line);
    
    if(line.find("Test") == 0){//test
      FLTypingControllerTestCase *testCase = new FLTypingControllerTestCase(*tc, *fleksyListener, api);
      testCases.push_back(testCase);
      getLastTestCase()->testInfo->testName = line;
    }
    else if(line[0] == '>'){ // text - send char
      string word = line.substr(1, line.length());
      for(int i = 0; i < word.length(); i++){
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = "SC";
        char c = word[i];
        action->isUpperCase = isupper(c);
        action->character = c;
        getLastTestCase()->addAction(action);
      }
    }
    else{//other commands like SR, SL, SU, SD, MC
      string first2Chars = line.substr(0, 2);
      if(first2Chars == "SR"){ //swipe right
        createAction(line);
      }
      else if(first2Chars == "SL"){ //swipe left
        createAction(line);
      }
      else if(first2Chars == "SU"){ //swipe up
        createAction(line);
      }
      else if(first2Chars == "SD"){ //swipe down
        createAction(line);
      }
      else if (line == "EOT"){ // End of test
        createAction(line);
      }
      else if (line == "MC end"){ // Moves cursor to the end of text
        createAction(line);
      }
      else if (line == "EC end"){ // Expected cursor is at the end
        createAction(line);
      }
      else if(first2Chars == "BF"){//back and forth swipe
        createAction(line);
      }
      else if(line == "SH"){//Shift pressed
        createAction(line);
      }
      else if(first2Chars == "NL"){//New Line, enter pressed
        createAction(line);
      }
      else if(first2Chars == "MC"){ //Move cursor
        FLTypingControllerAction *action = new FLTypingControllerAction();
        createAction(line, action);
        action->action = first2Chars;
        string cursorPos;
        if(string::npos != line.find_first_of("+")){
          int startIndx = (int)line.find_first_of("+") + 1;
          cursorPos = line.substr(startIndx, line.length());
          action->cursorPosition = atoi(cursorPos.c_str());
          action->cursorPosRelation = 1;
        }
        else if(string::npos != line.find_first_of("-")){
          int startIndx = (int)line.find_first_of("-") + 1;
          cursorPos = line.substr(startIndx, line.length());
          action->cursorPosition = atoi(cursorPos.c_str());
          action->cursorPosRelation = -1;
        }
        else{
          string cursorPos;
          if(string::npos != line.find_first_of(")")){
            int startIndx = (int)line.find_first_of(")") + 2; // ") 4"
            cursorPos = line.substr(startIndx, line.length());
          }
          else{
            cursorPos = line.substr(3, line.length());
          }
          action->cursorPosition = atoi(cursorPos.c_str());
          action->cursorPosRelation = 0;
        }
      }
      else if(first2Chars == "ET"){ // check output text
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = first2Chars;
        string text = line.substr(4, line.length());
        text.erase(text.length() - 1, 1);
        action->expectedOutput = text;
        getLastTestCase()->addAction(action);
      }
      else if(first2Chars == "EC"){ // check cursor position
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = first2Chars;
        action->cursorPosition = atoi(line.substr(3, line.length()).c_str());
        getLastTestCase()->addAction(action);
      }
      else if(first2Chars == "ST"){ // Screen Text
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = first2Chars;
        string text = line.substr(4, line.length());
        text.erase(text.length() - 1, 1);
        action->expectedOutput = text;
        getLastTestCase()->addAction(action);
      }
      else if(first2Chars == "KB"){ // Sets keyboard number
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = first2Chars;
        action->keyboardNumber = atoi(line.substr(2, line.length()).c_str());
        getLastTestCase()->addAction(action);
      }
      else if(first2Chars == "SH"){ // set shiftState
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = "SHC";
        int paren1Indx = (int)line.find_first_of("(") + 1;
        int paren2Indx = (int)line.find_first_of(")");
        string shiftState = line.substr(paren1Indx, paren2Indx - paren1Indx);
        //printf("SHIFT STATE: %s \n\n", shiftState.c_str());
        if(shiftState == "on"){
          action->expectedShiftState = true;
        }
        else{
          action->expectedShiftState = false;
        }
        getLastTestCase()->addAction(action);
      }
      else if(first2Chars == "AC"){ // set AutoCorrect
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = "AC";
        int paren1Indx = (int)line.find_first_of("(") + 1;
        int paren2Indx = (int)line.find_first_of(")");
        string acState = line.substr(paren1Indx, paren2Indx - paren1Indx);
        if(acState == "on"){
          action->autoCorrect = true;
        }
        else{
          action->autoCorrect = false;
        }
        getLastTestCase()->addAction(action);
      }
      else if(line.substr(0, 3) == "TBC"){ // check textblock cursor position
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = "TBC";
        int commaIndx = (int)line.find_first_of(",");
        int numOfChars = commaIndx - 5;
        string blockIndx = line.substr(5, numOfChars);
        string indexInBlock = line.substr(commaIndx + 1, (line.length() - (commaIndx + 1) - 1));
        action->blockIndex = atoi(blockIndx.c_str());
        action->indexInBlock = atoi(indexInBlock.c_str());
        getLastTestCase()->addAction(action);
      }
      else if(line.substr(0, 3) == "SEL"){ //select text
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = "SEL";
        int commaIndx = (int)line.find_first_of(",");
        int numOfChars = commaIndx - 5;
        string selStart = line.substr(5, numOfChars);
        string selEnd = line.substr(commaIndx + 1, (line.length() - (commaIndx + 1) - 1));
        action->selectionStart = atoi(selStart.c_str());
        action->selectionEnd = atoi(selEnd.c_str());
        getLastTestCase()->addAction(action);
      }
      else if(line.substr(0, 3) == "EUL"){ // check composing region (Expected Underline)
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = "EUL";
        int commaIndx = (int)line.find_first_of(",");
        int numOfChars = commaIndx - 5;
        string start = line.substr(5, numOfChars);
        string end = line.substr(commaIndx + 1, (line.length() - (commaIndx + 1) - 1));
        action->composingStart = atoi(start.c_str());
        action->composingEnd = atoi(end.c_str());
        getLastTestCase()->addAction(action);
      }
      else if(line.substr(0, 3) == "OUS"){ // send onUpdateSelection
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = "OUS";
        int paren1indx = (int)line.find_first_of("(") + 1;
        int paren2indx = (int)line.find_first_of(")");
        
        string substr = line.substr(paren1indx, paren2indx - paren1indx);
        vector<FLString> nums = split(FLStringMake(substr.c_str()), FLStringMake(","));
        
        action->onUpdateSelectionVals[0] = flatoi(nums[0]);
        action->onUpdateSelectionVals[1] = flatoi(nums[1]);
        action->onUpdateSelectionVals[2] = flatoi(nums[2]);
        action->onUpdateSelectionVals[3] = flatoi(nums[3]);
        getLastTestCase()->addAction(action);
      }
      else if(line.substr(0, 4) == "CAPS"){ // send onUpdateSelection
        FLTypingControllerAction *action = new FLTypingControllerAction();
        action->action = "CAPS";
        int paren1indx = (int)line.find_first_of("(") + 1;
        int paren2indx = (int)line.find_first_of(")");
        
        string substr = line.substr(paren1indx, paren2indx - paren1indx);
        if(substr == "on"){
          action->isUpperCase = true;
        }
        else{
          action->isUpperCase = false;
        }
        getLastTestCase()->addAction(action);
      }
    }
  }
}

int FLTypingControllerTester::getNumberFromSubstring(string substring){
  int endIndx = (int)substring.find_first_of(",");
  return atoi(substring.substr(0, endIndx).c_str());
}

void FLTypingControllerTester::printTestCases(){
  printf("Number of test cases: %li\n", testCases.size());
  for(int i = 0; i < testCases.size(); i++){
    FLTypingControllerTestCase *testCase = testCases[i];
    
    printf("TestName: %s \n", testCase->testInfo->testName.c_str());
    //printf("Comments: %s \n", testCase->comments.c_str());
    
    for(int k = 0; k < testCase->actions.size(); k++){
      FLTypingControllerAction *action = testCase->actions[k];
      
      printf("Action: %s\n", action->action.c_str());
      string character = action->character.c_str();
      if(character.length() > 0)
        printf("Character: %s\n", action->character.c_str());
      
      string expOutput = action->expectedOutput.c_str();
      if(expOutput.length() > 0){
        printf("Expected Otput:<%s>\n", action->expectedOutput.c_str());
        printf("CursorPosition: %i\n", action->cursorPosition);
      }
      
    }
  }
}


void FLTypingControllerTester::setup(){
  
  printf("Starting setup...\n");

  char jetResourcePath[PATH_MAX];
  snprintf(jetResourcePath, sizeof(jetResourcePath), "%s/encrypted/resourceArchive-en-US.jet", executableResourcesPathString.c_str());
  printf("Using Jet Resources at: '%s'\n", jetResourcePath);

  api->setResourceFile(jetResourcePath);
  api->loadResources();
  
  createFLTypingControllerTestCases();
  api->startTypingSession();
  api->setActiveKeyboard(FLKeyboardID_QWERTY_UPPER);
  printf("Setup finished.\n");
  
}

void FLTypingControllerTester::doBackSpace(){
  api->backspace();
}

void FLTypingControllerTester::runTests(bool breakOnFail){
  printf("Starting Tests\n");
  
//  api->startTypingSession(true);
//  
//  FLTypingControllerTestCase *testCase = new FLTypingControllerTestCase(*tc, *fleksyListener);
//  FLTypingControllerAction *action = new FLTypingControllerAction();
//  action->action = "SC";
//  char c = 'h';
//  action->isUpperCase = isupper(c);
//  action->character = c;
//  testCase->addAction(action);
//  testCase->testInfo->testName = "Custom Test";
//  testCase->run();
  
//  for (int i = 0; i < 10; i++){
//    api->backspace(true);
//    api->backspace();
//    api->nextSuggestion();
//    api->previousSuggestion();
//    api->space();
//    api->space(true);
//    
//    api->setActiveKeyboard(FLKeyboardID_NUMBERS);
//    api->setActiveKeyboard(FLKeyboardID_QWERTY);
//    api->setActiveKeyboard(FLKeyboardID_SYMBOLS);
//  }
//  return;
  
  for(int i = 0; i < testCases.size(); i++){
    printf("\n*****Running test %s******\n\n", testCases[i]->testInfo->testName.c_str());
    int result = 1;
    try{
      result = testCases[i]->run();
    }
    catch (std::runtime_error er) {
      printf("Error while running test: %s, Error: %s\n", testCases[i]->testInfo->testName.c_str(), er.what());
      CheckType error;
      error.isError = true;
      error.type = "Runtime Error: ";
      error.type.append(er.what());
      error.result.append(testCases[i]->getLastActionInfo());
      testCases[i]->testInfo->addCheckType(error);
    }
    catch(std::exception ex){
      printf("Exception while running test: %s, Exception: %s\n", testCases[i]->testInfo->testName.c_str(), ex.what());
      CheckType error;
      error.isError = true;
      error.type = ex.what();
      error.result.append(testCases[i]->getLastActionInfo());
      testCases[i]->testInfo->addCheckType(error);
    }
    
    if(result == 1){//failed test
      testCases[i]->testInfo->passed = false;
    }
    else{
      testCases[i]->testInfo->passed = true;
    }
    
    testInfos.push_back(testCases[i]->testInfo);
    deleteDataFromPreviousTest(*tc);
    
      if(breakOnFail && !testCases[i]->testInfo->passed){
        printf("\nTest %s FAILED!\n", testCases[i]->testInfo->testName.c_str());
        testCases[i]->testInfo->printTestInfo();
        return;
      }
  }
  
  printf("\nTest Results:\n");
  int numFailed = 0;
  int numPassed = 0;
  for(FLTestInfo *ti : testInfos){
    if(ti->passed){
      printf("%s: PASSED\n", ti->testName.c_str());
      numPassed++;
    }
    else{
      printf("%s: FAILED\n", ti->testName.c_str());
      ti->printTestInfo();
      numFailed++;
    }
  }
  deleteTestInfos();
  printf("FINISHED Running all tests. Fireworks! Party!!!\n");
  int totalTests = (int)testCases.size();
  float percentPass = ((float)numPassed / (float)totalTests) * 100;
  float percentFail = ((float)numFailed / (float)totalTests) * 100;
  printf("Number of tests run: %i, Passed: %i(%.2f%%), Failed: %i(%.2f%%)\n", totalTests, numPassed, percentPass,  numFailed,  percentFail);
}

