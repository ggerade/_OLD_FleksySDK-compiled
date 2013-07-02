//
//  FLDataCollector.h
//  FleksySDK
//
//  Created by Vadim Maximov on 6/27/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLDataCollector__
#define __FleksySDK__FLDataCollector__

#include <iostream>
#include <vector>
#include <string>
#include "FLEnums.h"
#include "FleksyListenerInterface.h"

class FLDataCollector{
public:
  FLDataCollector(FleksyListenerInterface &listener);
  ~FLDataCollector();
  
  void setIsCollectingData(bool isCollectingData);
  void setDataCollectionFilePath(std::string path);
  
  void processEvent(FLEventType event, ...);
  void writeEventsToFile();
  
  bool isDataCollectionEnabled();
  
private:
  FleksyListenerInterface &listener;
  std::vector<std::string>events;
  bool isCollectingData;
  std::string dataWritePath;
  
  void recordEvent(std::string event);
 
  std::string floatToString(float value);
  std::string longToString(long long value);
  std::string doubleToString(double value);
};

#endif /* defined(__FleksySDK__FLDataCollector__) */
