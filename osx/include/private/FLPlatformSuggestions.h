//
//  FLPlatformSuggestions.h
//  FleksyLib
//
//  Created by Vadim Maximov on 3/6/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksyLib__FLPlatformSuggestions__
#define __FleksyLib__FLPlatformSuggestions__

#include <iostream>
#include "PatternRecognizer/Structures.h"

class FLPlatformSuggestions{
public:
  FLPlatformSuggestions();
  ~FLPlatformSuggestions();
  void setProcessedResults(FLString processedResults);
  FLString *getProcessedResults();
  void setProcessedRequestID(FLString requestID);
  FLString getProcessedRequestID();
  
private:
  FLString *processedResults;
  FLString processedRequestID;
};

#endif /* defined(__FleksyLib__FLPlatformSuggestions__) */
