#ifndef FLREQUEST_H
#define FLREQUEST_H

#include <string>
#include <vector>
#include "FLTouchPoint.h"
#include "PatternRecognizer/Platform.h"
#include "FLUnicodeString.h"

class FLRequestDataHolder{
  
public:
  FLUnicodeString hint;
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
  void setHasSimulatedPoints(bool isSimulated);
  bool getHasSimulatedPoints();
  
private:
  std::vector<FLPoint> points;
  bool hasSimulatedPoints;
  FLUnicodeString textEntered;
};

#endif
