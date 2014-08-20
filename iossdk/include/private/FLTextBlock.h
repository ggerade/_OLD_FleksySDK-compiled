#ifndef FLTEXTBLOCK_H
#define FLTEXTBLOCK_H

#include "FLRequestDataHolder.h"
#include "FLTextBlock.h"
#include "PatternRecognizer/Platform.h"
#include "FleksyListenerInterface.h"
#include "FLKeyboard.h"
#include "FLUnicodeString.h"

class SystemsIntegrator;
class FLTypingController;
class FLTextBlock;

/*
 * class SplittageMemo
 * When the engine gives a space broken suggestion which the user accepts, as a general rule
 * we just leave that text block unchaged, with both words combined. However, if the user does
 * something that would modify the text in that text block, we split the two words apart into
 * their own text blocks. This presents a problem for data analysis, because neither new text
 * block knows what its origins were, so we lose information in the most important case for
 * space breaking: when we didn't do what the user wanted.
 *
 * To solve this problem, we use Splittage Memo, which carries a link to the original, unsplit
 * text block. This gives us information about the original text, points, and suggestions.
 *
 * The splittage memo becomes responsible for the life of the orig text block, and when either
 * of a or b is deleted, it is responsible for setting the pointer to itself on its splittage
 * memo to null.
 */
class SplittageMemo {
public:
  SplittageMemo(FLTextBlock *orig_, FLTextBlock *a_, FLTextBlock *b_);
  ~SplittageMemo();
  
  FLTextBlock *orig;
  FLTextBlock *a;
  FLTextBlock *b;
};

class FLTextBlock{
public:
	FLTextBlock();
  ~FLTextBlock();
  
  //Getters/Setters
  void setCorrectedText(const FLUnicodeString &text);
  FLUnicodeString getCorrectedText();
  void setTextEntered(const FLUnicodeString &text);
  FLUnicodeString getTextEntered() const;
  int getLength() const;
  int getLengthWithSpace() const;
  bool isPunctuationInside() const;
	void setIsPunctuationInside(bool isPunctuation);
  bool isSpaceEnabled() const;
  void setIsSpaceEnabled(bool isSpaceEnabled);
  bool isNewLineTextBlock() const;
  bool isSymbolsTextBlock() const;
  void setIsSymbolsTextBlock(bool symbol);
  bool isEmojiTextBlock() const;
  bool isSmileyTextBlock() const;
  void setIsEmojiTextBlock(bool isEmoji);
  bool isEndSentence() const;
  bool isBeginSentence() const;
  void setUserEditedText(bool edited) { userEditedText = edited; }
  bool isUserEditedText() const;
  void setIsAccuratelyTyped(bool isAccuratelyTyped);
  bool getIsAccuratelyTyped() const;
  bool isVirgin() const; // True if this text block contains no text or spaces.
  
  ////////// Functions for managing suggestions. //////////
  
  int getSuggestionIndex() const;
  std::vector<FLUnicodeString> getSuggestions() const;
  
  void resetSuggestionIndex();
  void setSuggestionIndex(int suggIndex);
  
  void setSuggestions(const std::vector<FLUnicodeString>& suggestions);
  void clearSuggestion() { _suggestions.clear(); }
  
  ////////// Unclassified functions. ///////////
  
	FLRequestDataHolder *getRequest();
  FLUnicodeString getText() const;
  
  
	bool getIsExactEntry() const;
  bool isCorrected() const;
  
  void addCharacter(FLPoint p, const FLUnicodeString &c, int index, std::shared_ptr<FLKeyboard> keyboard);
  void setRequestPoints(const std::vector<FLPoint> &points);
	
  FLUnicodeString deleteCharacter(int indx);
  void cleanTextBlock();
  FLUnicodeString getTextToCorrect();
  
  FLUnicodeString displayString(int tbNumber = -1, bool withPoints = false);
  void printSelf(int tbNumber = -1, bool withPoints = false);
  void printfSelf(int tbNumber = -1, bool withPoints = false);
  FLUnicodeString getTextBlockInfo(int tbNumber);
  FLUnicodeString toLowerCase(const FLUnicodeString &string);
  
  bool containsNonAlphaCharacters(SystemsIntegrator* fleksy) const;
  bool containsApostrophe() const;
  bool isSplitWithSpace() const;
  void setUserCapitalization(bool isUserSet);
  bool userSetCapitalization() const;
  
  void setReplacedSuggestion(bool replaced) { _replacedSuggestion = replaced; }
  bool replacedSuggestion() const { return _replacedSuggestion; }
  
  int getLengthBeforePreviousUpdate() const;
  int getLengthDiff() const;
  int getVisibleLength() const;
  
  FLUnicodeString matchCase(const FLUnicodeString &word);
  
  void setMemo(std::shared_ptr<SplittageMemo> memo);
  std::shared_ptr<SplittageMemo> getMemo() const;
  
  /*
   Change the current corrected word to the new word. If the word is not in the suggestion 
   list, nothing happens and "false" is returned. This method will modify the suggestion index and
   the corrected text
   */
  bool changeSuggestedWordTo(const FLUnicodeString &word);
  
  // Functions for debug.
  void rememberContext(const std::vector<FLUnicodeString> &tokens) { context = tokens; }
  std::vector<FLUnicodeString> getContext() const { return context; }
  
private:
  std::vector<FLUnicodeString> _suggestions;
	int suggestionIndx;
  
	FLRequestDataHolder *request;
	FLUnicodeString correctedText;
	bool isPunctuation;
  bool isSpaceAfterTextBlock;
  bool isExactEntry; // if typed the word accuratly
  bool isSymbolTextBlock;
  bool addedWordToDictionary;
  bool isUserSetCapitalization;
  bool userEditedText;
  bool isAccuratelyTyped;
  bool isEmoji;
  bool _replacedSuggestion;
  
  void printTextBlock() const;
  
  int lengthBeforePreviousUpdate = 0;
  void setLengthBeforePreviousUpdate(int length);
  
  // Text blocks that were space broken and subsequently modified will carry information about
  // their life before being split apart to help with data collection.
  std::shared_ptr<SplittageMemo> _memo;
  
  // Data For debug.
  // The context that was used when the suggestions for this text block were generated.
  std::vector<FLUnicodeString> context;
};

#endif
