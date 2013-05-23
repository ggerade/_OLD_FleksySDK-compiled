//
//  FLMotionEventManager.h
//  FleksySDK
//
//  Created by Vadim Maximov on 5/17/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK__FLMotionEventManager__
#define __FleksySDK__FLMotionEventManager__

#include "FleksyListenerInterface.h"


class SystemsIntegrator;

class FLMotionEventManager{
  
  

public:
  FLMotionEventManager(FleksyListenerInterface &listener, SystemsIntegrator *sysIntegrator);
  
  void onTouchDown(float x, float y, int ID, long long time);
  void onMove(float x, float y, int ID, long time);
  void onTouchUp(float x, float y, int ID, long time);
  
private:
  FleksyListenerInterface &listener;
  SystemsIntegrator *sysIntegrator;
  
};



#include <iostream>

#endif /* defined(__FleksySDK__FLMotionEventManager__) */
