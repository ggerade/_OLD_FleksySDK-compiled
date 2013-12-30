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
  
  //Single shot events
  void addedWordToDictionary();
  
  //Other
  void setIsTracking(bool isTracking);
  bool isTrackingEvents();
  void setCurrentKeyboardLayout(const FLUnicodeString &currentKeyboardLayout);
  
private:
  FleksyListenerInterface &listener;
  int threshold;
  bool isTracking;
  //Event,number of events
  std::map<FLUnicodeString, int> events;
  long lastEventTime;
  FLUnicodeString lastEvent;
  FLUnicodeString currentKeyboardLayout;
  
  
  void sendEvent(const FLUnicodeString &event);
  std::map<FLUnicodeString, int>::iterator findEvent(const FLUnicodeString &event);
  bool hasReachedThreshold(int numOfEvents);
  void processEvent(const FLUnicodeString &event);
  FLUnicodeString intToString(int integer);
  void swipeRight();
  void spaceBarPress();
  
  
  FLUnicodeString getLayoutName();
};


#endif /* defined(__FleksySDK__FLTrackEvents__) */
