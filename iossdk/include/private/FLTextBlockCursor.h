#ifndef __FleksyApiTest__TBCursor__
#define __FleksyApiTest__TBCursor__

#include <iostream>
#include <vector>
#include "FLTextBlock.h"

namespace Fleksy {
  class TBCursorIntegrityError : public Exception {
  public:
    explicit TBCursorIntegrityError(std::string message, std::string filename = "", int lineNumber = 0) {
      init(message, filename, lineNumber);
    }
  };
}

class FLTypingController;

class FLTextBlockCursor{
  
public:
  FLTextBlockCursor(std::vector<FLTextBlock*> &tbs, FLTextBlock *tb, int textBlockIndex, int indexInTextBlock, FLTypingController *tc);
  ~FLTextBlockCursor() {};
  
  FLTextBlock* getCurrentTextBlock();// const;
  FLTextBlock* getPreviousTextBlock();// const;
  FLTextBlock* getNextTextBlock();// const;
  int getIndexOfCurrentTextBlockInVector() const;
  int getIndexInTextBlock() const;
  
  void decrementIndexInTextBlock(int amount);
  void incrementIndexInTextBlock(int amount, const std::string &who);
  void decrementIndexInTextBlock() { decrementIndexInTextBlock(1); }
  void incrementIndexInTextBlock(const std::string &who) { incrementIndexInTextBlock(1, who); }

  void decrementVectorIndex();
  void incrementVectorIndex();
  
  void set(FLTextBlock *tb, int indexInTextBlock);
  void updateToPosition(int userCursorPosition, FleksyListenerInterface &out, const char *caller);
  void updateTextBlockCursor(FLTextBlock *tb, int tbIndex);
  void closeBlockAndAssignNew();
  void setCurrentTextBlock(FLTextBlock *tb);
  void setIndexInTextBlock(int indx);
  
  // Debug functions.
  void testIntegrity(const std::vector<FLTextBlock*> *ptrToTextBlocks);
  bool lostIntegrity(const std::vector<FLTextBlock*> *ptrToTextBlocks);
  
private:
  // The following three lines are for debugging a problem with invalid FLTextBlock pointers.
  FLTypingController *_tc;
  std::string _lastCaller = "";
  void testIfEverythingIsAlright();
  
  FLTextBlock *currentTextBlock;
  int indexOfCurrentTextBlockInVector;
  int indexInTextBlock;
  std::vector<FLTextBlock*> &textBlocks;
  
  void assignNewTextBlock();
  
  /*
   * Any text blocks which contain no text (or spaces) are removed in preparation for moving
   * the textblock cursor.
   */
  void cleanUpTextBlocks();
  
  /*
   * Some text blocks (eg. punctuation, newline, etc) don't join together with additional
   * characters. This function tells you if a text block is like that.
   */
  bool dontAppendToTextBlock(const FLTextBlock * const tb) const;
};

#endif
