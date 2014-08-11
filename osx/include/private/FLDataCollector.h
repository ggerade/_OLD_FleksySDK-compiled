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
#include "FLUnicodeString.h"

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
  
  void processEvent(FLEventType event, ...);
  void processEvent(const FLUnicodeString &eventData);
  
  void writeEventsToFile(bool writeAsync = false);
  std::string writeGameEventsToFile();
  
  void setFileHeader(std::string fileHeader);
  void appendToFileHeader(std::string info);
  
  /*
   * Compresses and encrypts data to file. Use this to create file for any kind of data.
   * FLUicodeString data - data to write to file
   * string directory - directory where files can be written
   * Directory path is /path/to/directory (no / at the end)
   * Returns a full path to the encrypted data file (<directory>/data.xxx) or empty string if fails to write data to file
   */

  FLUnicodeString writeDataToFile(const FLUnicodeString &data, const FLUnicodeString directory);
  FLUnicodeString getLastEvents(int numOfEvents);
  FLUnicodeString getLastSessionEvents();

private:
  FleksyListenerInterface &listener;
  std::vector<FLUnicodeString>events;
  FLUnicodeString tempEvents;
  bool isCollectingData;
  std::string dataWritePath;
  std::string fileHeader;
  bool isFileReadyForUpload;
  bool recievedPointEvent;
  
  FLTrackEvents *tracker = NULL;
  
  void recordEvent(const FLUnicodeString &eventData, FLEventType type);
 
  FLUnicodeString floatToString(float value);
  FLUnicodeString longToString(long long value);
  FLUnicodeString doubleToString(double value);
  std::string getEncryZipFilePath();
  std::string getEventFilePath();
  
  bool file_exists(const char * filename);
  
  void writeToFile();
  static void* writeToFileWrapper(void *arg);
  
  void encryptAndCompressDataToFile(const FLUnicodeString &data);
  std::string get_file_contents(const char *filename);
  void deleteFile(const char * filePath);
  
  bool isTrackerEvent(FLEventType event);
  bool isDataEvent(FLEventType event);
  
  std::string getDataWritePath();
};

#endif /* defined(__FleksySDK__FLDataCollector__) */
