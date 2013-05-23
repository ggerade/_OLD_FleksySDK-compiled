#ifndef FLPOINT_H
#define FLPOINT_H
#include "PatternRecognizer/FLPoint.h"

class FLTouchPoint{
  
public:
	FLTouchPoint(float x, float y, long long time = 0);
  float getX();
  float getY();
  long long getTime();
  FLPoint getPoint();
private:
  FLPoint point;
  long long time;
};



#endif
