//
//  FLTypingControllerTester.h
//  FleksyApiTest
//
//  Created by Vadim Maximov on 2/4/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef FLTYPINGCONTROLLERTESTER
#define FLTYPINGCONTROLLERTESTER

#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "FLTypingController.h"
#include "FLTypingControllerTestCase.h"
#include "FleksyListenerImplC.h"
#include "FleksyAPI.h"
#include "FLTestInfo.h"


class FLTypingControllerTester{
  
public:
  FLTypingControllerTester(char *executableResourcesPath);
  ~FLTypingControllerTester();
  void setup();
  bool runTests(bool breakOnFail);
  void deleteTestInfos();
  void doBackSpace();
private:
  
  string executableResourcesPathString;

  FleksyAPI *api = NULL;
  FleksyListenerImplC *fleksyListener = NULL;
  FLTypingController *tc = NULL;
  
  std::vector<FLTypingControllerTestCasePtr> testCases;
  std::vector<FLTestInfoPtr> testInfos;
  
  void createFLTypingControllerTestCases();
  void createAction(std::string line, FLTypingControllerActionPtr *a = NULL);
  FLTypingControllerTestCasePtr getLastTestCase();
  void deleteDataFromPreviousTest(FLTypingController &tc);
  void printTestCases();
  int getNumberFromSubstring(std::string substring);
};

#endif
