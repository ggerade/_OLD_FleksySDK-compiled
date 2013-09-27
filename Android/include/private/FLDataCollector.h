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
#include <pthread.h>
#include "FLEnums.h"
#include "FleksyListenerInterface.h"
#include "FLTrackEvents.h"

class FLDataCollector{
public:
  FLDataCollector(FleksyListenerInterface &listener);
  ~FLDataCollector();
  
  //For recording all events that get uploaded to the Amazon S3
  void setIsCollectingData(bool isCollectingData);
  
  bool isDataCollectionEnabled();
  void setIsGaming(bool isGaming);
  bool getIsGaming();
  
  //For events that go off to Bugsense or TestFlight or other places
  void setIsTrackingEvents(bool isTracking);
  
  void setDataCollectionFilePath(std::string path);
  void setFileHeader(std::string fileHeader);
  
  void processEvent(FLEventType event, ...);
  void processEvent(std::string event, std::string eventData);
  
  void writeEventsToFile(bool writeAsync = false);
  std::string writeGameEventsToFile();

private:
  FleksyListenerInterface &listener;
  std::vector<std::string>events;
  std::vector<std::string>gameEvents;
  std::string tempEvents;
  bool isCollectingData;
  bool isGaming;
  std::string dataWritePath;
  std::string fileHeader;
  bool isFileReadyForUpload;
  
  FLTrackEvents *tracker = NULL;
  
  void recordEvent(std::string eventData, FLEventType type);
 
  std::string floatToString(float value);
  std::string longToString(long long value);
  std::string doubleToString(double value);
  std::string getEncryZipFilePath();
  std::string getEventFilePath();
  
  bool file_exists(const char * filename);
  
  void writeToFile();
  static void* writeToFileWrapper(void *arg);
  
  void encryptAndCompressDataToFile(std::string data);
  std::string get_file_contents(const char *filename);
  void deleteFile(const char * filePath);
  
  bool isTrackerEvent(FLEventType event);
  
  std::string getDataWritePath();
};

#endif /* defined(__FleksySDK__FLDataCollector__) */
