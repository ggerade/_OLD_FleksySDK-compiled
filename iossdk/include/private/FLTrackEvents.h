//
//  FLTrackEvents.h
//  FleksySDK
//
//  Created by Vadim Maximov on 5/6/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLTrackEvents__
#define __FleksySDK__FLTrackEvents__

#include <iostream>
#include <map>
#include "FleksyListenerInterface.h"
#include "TimeFunctions.h"
#include "FLUnicodeString.h"

class FLTrackEvents{
  
public:
  FLTrackEvents(FleksyListenerInterface &listener);
  
  //Threshold based events
  void backspaceButtonPress();
  void swipeLeft();
  void swipeRight(float length);
  void swipeUp();
  void swipeDown();
  void switchedKeyboard(FLKeyboardID id);
  void wordTyped();
  void wordCorrected(FLUnicodeString &event);
  void wordCorrectedInternal(FLUnicodeString &event);
  void correctedCharacters(int numOfCorrections);
  void missedAllCharacters();
  
  //Single shot events
  void addedWordToDictionary();
  
  //Other
  void setIsTracking(bool isTracking);
  bool isTrackingEvents();
  
private:
  FleksyListenerInterface &listener;
  int threshold;
  bool isTracking;
  //Event,number of events
  std::map<FLUnicodeString, int> events;
  long lastEventTime;
  
  
  void sendEvent(FLUnicodeString &data);
  static void* sendEventWrapper(void *arguments);
  void sendEventAsync(FLUnicodeString &data);
  
  FLUnicodeString createEventJSON(const FLUnicodeString &event, const FLUnicodeString &message, const FLUnicodeString &value);
  std::map<FLUnicodeString, int>::iterator findEvent(const FLUnicodeString &event);
  bool hasReachedThreshold(int numOfEvents);
  void processEvent(const FLUnicodeString &event, const FLUnicodeString &message);
  FLUnicodeString intToString(int integer);
  void swipeRight();
  void spaceBarPress();

};


#endif /* defined(__FleksySDK__FLTrackEvents__) */
