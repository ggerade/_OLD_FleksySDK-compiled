//
//  TestInfo.cpp
//  FleksyApiTest
//
//  Created by Vadim Maximov on 4/5/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#include "FLTestInfo.h"

using namespace std;

FLTestInfo::FLTestInfo(string testName){
  this->testName = testName;
  passed = false;
}

void FLTestInfo::addCheckType(CheckType type){
  testStages.push_back(type);
}

void FLTestInfo::printTestInfo(){
  printf("%s details:\n", testName.c_str());
  for(CheckType check : testStages){
    printf("Check Type: %s, Result: %s\n", check.type.c_str(), check.result.c_str());
  }
}