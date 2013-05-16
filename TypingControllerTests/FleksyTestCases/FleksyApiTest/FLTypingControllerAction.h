
#ifndef __FleksyApiTest__FLTypingControllerAction__
#define __FleksyApiTest__FLTypingControllerAction__

#include <iostream>

class FLTypingControllerAction{
public:
  std::string action; //send character(SC), SR, SL, SU, SD, MC
  bool isUpperCase = false;
  int cursorPosition; // used if action is MC = moved cursor or O = expected output
  int keyboardNumber;
  std::string character; //userd if action is send character
  std::string expectedOutput; // used if action is check O.
  int cursorPosRelation; //-1 = -, 1 = +, 0 = exact position
  int blockIndex;
  int indexInBlock;
  int composingStart;
  int composingEnd;
  int selectionStart;
  int selectionEnd;
  int suggestionIndex = -1;
  
  bool expectedShiftState; //true = on, false = off
  int onUpdateSelectionVals[4] = {0, 0, 0, 0};
  bool autoCorrect;
};


#endif /* defined(__FleksyApiTest__FLTypingControllerAction__) */
