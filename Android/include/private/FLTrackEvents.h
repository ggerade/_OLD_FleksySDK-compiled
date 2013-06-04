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

class FLTrackEvents{
  
public:
  FLTrackEvents(FleksyListenerInterface &listener);
  
  //Threshold based events
  void backspaceButtonPress();
  void swipeLeft();
  void swipeRight(bool buttonPress);
  void swipeUp();
  void swipeDown();
  void switchedKeyboard(FLKeyboardID id);
  
  //Single shot events
  void addedWordToDictionary();
  
  //Other
  void setIsTracking(bool isTracking);
  void setCurrentKeyboardLayout(std::string currentKeyboardLayout);
  
private:
  FleksyListenerInterface &listener;
  int threshold;
  bool isTracking;
  //Event,number of events
  std::map<std::string, int> events;
  long lastEventTime;
  std::string lastEvent;
  std::string currentKeyboardLayout;
  
  
  void sendEvent(FLString event);
  std::map<std::string, int>::iterator findEvent(std::string event);
  bool hasReachedThreshold(int numOfEvents);
  void processEvent(std::string event);
  std::string intToString(int integer);
  void swipeRight();
  void spaceBarPress();
};


#endif /* defined(__FleksySDK__FLTrackEvents__) */
