//
//  GenericCalculatorCPP.h
//  Fleksy
//
//  Created by Kostas Eleftheriou on 6/25/11.
//  Copyright 2011 Syntellia Inc. All rights reserved.
//

#pragma once

#include "Structures.h"


#define CALCULATOR_MAX_STACK_SIZE 5


class GenericCalculatorCPP {
  
protected:
  CalculatorStateStruct state[CALCULATOR_MAX_STACK_SIZE];
  int stackIndex;
  
  
public:
  
  GenericCalculatorCPP();
  void reset();
  void pushState();
  void popState();
  void setState(CalculatorStateStruct s);
  CalculatorStateStruct getState();

  
};

