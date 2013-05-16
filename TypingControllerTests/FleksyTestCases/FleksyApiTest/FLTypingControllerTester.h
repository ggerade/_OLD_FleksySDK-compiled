//
//  FLTypingControllerTester.h
//  FleksyApiTest
//
//  Created by Vadim Maximov on 2/4/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FLTYPINGCONTROLLERTESTER
#define FLTYPINGCONTROLLERTESTER

#include <iostream>
#include <fstream>
#include "FLTypingController.h"
#include "FLTypingControllerTestCase.h"
#include "FleksyListenerImplC.h"
#include "FleksyAPI.h"
#include "FLTestInfo.h"


class FLTypingControllerTester{
  
public:
  FLTypingControllerTester();
  ~FLTypingControllerTester();
  void setup();
  void runTests(bool breakOnFail);
  void deleteTestInfos();
  void doBackSpace();
private:
  
  FleksyAPI *api;
  FleksyListenerImplC *fleksyListener;
  FLTypingController *tc;
  
  std::vector<FLTypingControllerTestCase*> testCases;
  std::vector<FLTestInfo*> testInfos;
  
  void createFLTypingControllerTestCases();
  void createAction(std::string line, FLTypingControllerAction *a = NULL);
  FLTypingControllerTestCase *getLastTestCase();
  void deleteDataFromPreviousTest(FLTypingController &tc);
  void printTestCases();
  int getNumberFromSubstring(std::string substring);
};

#endif
