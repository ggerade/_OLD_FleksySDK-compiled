#ifndef FLREQUEST_H
#define FLREQUEST_H

#include <string>
#include <vector>
#include "FLTouchPoint.h"
#include "PatternRecognizer/Platform.h"
#include "FLSocketsCommon.h"
#include "FLUnicodeString.h"

class FLRequestDataHolder{
  
public:
	FLRequestDataHolder();
	void addPoint(FLPoint p, int indx);
	void removePointAt(int indx);
	void removeLastPoint();
	void addCharacter(const FLUnicodeString &c, int indx);
	FLUnicodeString deleteCharacterAt(int indx);
	FLUnicodeString getTextEntered();
	void setTextEntered(const FLUnicodeString &text);
	std::vector<FLPoint> getPoints(bool skipInvalid);
	void setPoints(const std::vector<FLPoint> &points);
  void resetRequest();
  void clearPoints();
  void printPoints();
  
private:
  std::vector<FLPoint> points;
  FLUnicodeString textEntered;
};

#endif
