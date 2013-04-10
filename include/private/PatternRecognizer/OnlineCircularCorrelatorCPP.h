//
//  OnlineCircularCorrelatorCPP.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 6/25/11.
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#pragma once

#include "GenericCalculatorCPP.h"
#include "Structures.h"


class OnlineCircularCorrelatorCPP : public GenericCalculatorCPP {
  
public:
   
  void addSplitAngle1(FLPoint a, FLPoint b, float w1, float w2);
  void swapSplitAngle1(FLPoint a, FLPoint b, FLPoint c, FLPoint d, float w1, float w2, float w3, float w4);
  StandardDeviationResult getData(bool mean);
  float getMean();
  
};
