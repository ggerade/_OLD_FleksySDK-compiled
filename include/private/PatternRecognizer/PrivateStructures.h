//
//  Structures.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 6/22/11.
//  Copyright 2011 Syntellia Inc. All rights reserved.
//
#ifndef PRIVATE_STRUCTURES_H
#define PRIVATE_STRUCTURES_H

//#include "VarianceCalculatorCPP.h"
#include "OnlineCircularCorrelatorCPP.h"

//TODO do as class, with reset method
typedef struct Calculators {
  
  //OnlinePPMCCalculator* calcL;
  //OnlinePPMCCalculator* calcR;
  //OnlinePPMCCalculator* calcLog;
  
  OnlineCircularCorrelatorCPP* ccalc;
  //VarianceCalculatorCPP* vcalc;
  
} Calculators;

#endif