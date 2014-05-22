#ifndef __FleksyApiTest__TBCursor__
#define __FleksyApiTest__TBCursor__

#include <iostream>
#include <vector>
#include "FLTextBlock.h"

class FLTextBlockCursor{
  
public:
  FLTextBlockCursor(std::vector<FLTextBlock*> &tbs, FleksyListenerInterface &listener, FLTextBlock *tb, int textBlockIndex, int indexInTextBlock);
  ~FLTextBlockCursor();
  
  FLTextBlock *getCurrentTextBlock();
  
  void decrementIndexInTextBlock(int amount);
  void incrementIndexInTextBlock(int amount, const std::string &who);
  void decrementIndexInTextBlock() { decrementIndexInTextBlock(1); }
  void incrementIndexInTextBlock(const std::string &who) { incrementIndexInTextBlock(1, who); }

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
  
  // Debug functions.
  void testIntegrity(const std::vector<FLTextBlock*> *ptrToTextBlocks);
  bool lostIntegrity(const std::vector<FLTextBlock*> *ptrToTextBlocks);
  
private:
  FLTextBlock *currentTextBlock;
  int indexOfCurrentTextBlockInVector;
  int indexInTextBlock;
  std::vector<FLTextBlock*> &textBlocks;
  FleksyListenerInterface &out;
  
  void setIndexOfCurrentTextBlockInVector(int indx);
  void assignNewTextBlock();
  
  void deleteFromVectorLocation(int index);
  bool checkIfSafeAndDeleteFromCurrentLocation();
  void insertAtLocation(int index);
  bool createNewTextBlockIfNextToPunctuation(FLTextBlock *tb, int i);
  void updateTextBlockCursor(int vectorIndex, int indexInTextBlock);
};

#endif
