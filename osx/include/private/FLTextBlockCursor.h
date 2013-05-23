#ifndef __FleksyApiTest__TBCursor__
#define __FleksyApiTest__TBCursor__

#include <iostream>
#include <vector>
#include "FLTextBlock.h"

class FLTextBlockCursor{
  
public:
  FLTextBlockCursor(std::vector<FLTextBlock*> &tbs, FleksyListenerInterface &listener, FLTextBlock *tb, int textBlockIndex, int indexInTextBlock);
  ~FLTextBlockCursor();
  
  void assignNewTextBlock();
  
  FLTextBlock *getCurrentTextBlock();
  
  void decrementIndexInTextBlock();
  void incrementIndexInTextBlock(std::string who);
  void dectementVectorIndex();
  void incrementVectorIndex();
  
  int getIndexOfCurrentTextBlockInVector();
  int getIndexInTextBlock();
  
  FLTextBlock* getPreviousTextBlock();
  FLTextBlock* getNextTextBlock();
  
  void updateTextBlockCursor(FLTextBlock *tb, int vectorIndex, int indexInTextBlock);
  void updateTextBlockCursor(int userCursorPosition, FleksyListenerInterface &out);
  void updateTextBlockCursorToBlock(FLTextBlock *tb, int vectorIndex, int indexInTextBlock);
  void closeBlockAndAssignNew();
  void setCurrentTextBlock(FLTextBlock *tb);
  void setIndexInTextBlock(int indx);
  
private:
  FLTextBlock *currentTextBlock;
  int indexOfCurrentTextBlockInVector;
  int indexInTextBlock;
  std::vector<FLTextBlock*> &textBlocks;
  FleksyListenerInterface &out;
  
  
  void setIndexOfCurrentTextBlockInVector(int indx);
  
  void deleteFromVectorLocation(int index);
  bool checkIfSafeAndDeleteFromCurrentLocation();
  void insertAtLocation(int index);
  bool createNewTextBlockIfNextToPunctuation(FLTextBlock *tb, int i);
  void updateTextBlockCursor(int vectorIndex, int indexInTextBlock);
};

#endif
