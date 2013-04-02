//
//  FleksyTester.cpp
//  FleksySample1
//
//  Created by Kosta Eleftheriou on 3/25/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#include "FleksyTester.h"

#include "Fleksy.h"
#include "FleksyListenerImplC.h"

void FleksyTester::run(const char* resourcePath) {
  
  FleksyListenerImplC* listener = new FleksyListenerImplC();
  FleksyAPI* api = new FleksyAPI(*listener);
  
  api->setResourcePath(resourcePath);
  api->loadResources();
  
  ///////  BEGIN USAGE  ///////
  
  printf("\n [type hello]\n\n");
  api->sendTap(195, 108, 0);
  api->sendTap(80, 36, 0);
  api->sendTap(300, 100, 0);
  api->sendTap(300, 100, 0);
  api->sendTap(270, 40, 0);
  api->space();
  
  printf("\n [type world]\n\n");
  api->sendTap(48, 36, 0);
  api->sendTap(270, 36, 0);
  api->sendTap(112, 36, 0);
  api->sendTap(302, 108, 0);
  api->sendTap(88, 108, 0);
  api->space();
  
  printf("\n [add a period]\n\n");
  api->space();
  
  printf("\n [change period to exclamation mark]\n\n");
  api->nextSuggestion();
  api->nextSuggestion();
  api->nextSuggestion();
  
  printf("\n [delete exclamation mark]\n\n");
  api->backspace();
  
  printf("\n [change to next suggestion of \"world\"]\n\n");
  api->nextSuggestion();
  
  printf("\n [change to previous suggestion (back to \"world\")]\n\n");
  api->previousSuggestion();
  
  printf("\n [delete words]\n\n");
  api->backspace();
  api->backspace();
}