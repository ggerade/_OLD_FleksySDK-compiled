
#ifndef __FleksyApiTest__FLKeyMap__
#define __FleksyApiTest__FLKeyMap__

#include <iostream>
#include "FLString.h"
#include "FLPoint.h"
#include "FleksyDefines.h"


class FLKeyMap{
  
public:
  FLKeyMap();
  ~FLKeyMap();
  void set(FLChar c, FLPoint point);
  FLPoint get(FLChar c);
  FLChar getNearestChar(FLPoint point);
  
private:
  FLPoint keys[KEY_MAX_VALUE];
};

#endif
