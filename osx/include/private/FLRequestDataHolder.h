#ifndef FLREQUEST_H
#define FLREQUEST_H

#include <string>
#include <vector>
#include "FLTouchPoint.h"
#include "PatternRecognizer/Platform.h"
#include "FLSocketsCommon.h"

class FLRequestDataHolder{
  
public:
	FLRequestDataHolder();
	void addPoint(FLPoint p, int indx);
	void removePointAt(int indx);
	void removeLastPoint();
	void addCharacter(FLChar c, int indx);
	FLChar deleteCharacterAt(int indx);
	FLString getTextEntered();
	void setTextEntered(FLString text);
	std::vector<FLPoint> getPoints(bool skipInvalid);
	void setPoints(std::vector<FLPoint>);
  void resetRequest();
  void clearPoints();
  
private:
  std::vector<FLPoint> points;
  FLString textEntered;
};

#endif
