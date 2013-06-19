//
//  TestInfo.h
//  FleksyApiTest
//
//  Created by Vadim Maximov on 4/5/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksyApiTest__TestInfo__
#define __FleksyApiTest__TestInfo__

#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct CheckType{
  std::string type;
  std::string result;
  bool isError = false;
};

class FLTestInfo{
  
public:
  FLTestInfo(std::string testName);
  void printTestInfo();
  void addCheckType(CheckType type);
  std::string testName;
  bool passed;
  
private:
  
  
  std::vector<CheckType> testStages;
};

typedef std::shared_ptr<FLTestInfo> FLTestInfoPtr;

#endif /* defined(__FleksyApiTest__TestInfo__) */
