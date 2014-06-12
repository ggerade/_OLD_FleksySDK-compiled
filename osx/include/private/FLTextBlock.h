#ifndef FLTEXTBLOCK_H
#define FLTEXTBLOCK_H

#include "FLSuggestionsContainer.h"
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
	FLTextBlock(FleksyListenerInterface &listener);
  ~FLTextBlock();
  
  //Getters/Setters
  FLSuggestionsContainer *getResponse();
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
  bool isUserEditedText() const;
  void setIsAccuratelyTyped(bool isAccuratelyTyped);
  bool getIsAccuratelyTyped() const;
  bool isVirgin() const; // True if this text block contains no text or spaces.
  
	FLRequestDataHolder *getRequest();
  FLUnicodeString getText() const;
  int getSuggestionIndex() const;
  int getSuggestionIndex_dataexplorer() const;
  
  std::vector<FLUnicodeString> getSuggestions() const;
  
  void setSuggestionIndex(int suggIndex);
	bool getIsExactEntry() const;
  bool isCorrected() const;
  
  void addCharacter(FLPoint p, const FLUnicodeString &c, int index, FLKeyboardPtr &keyboard);
  void setSuggestions(const std::vector<FLUnicodeString>& suggestions);
  void setRequestPoints(const std::vector<FLPoint> &points);
	
	void deleteText();
  FLUnicodeString deleteCharacter(int indx, FLTypingController *tc, int oldLength, int oldIndx,  int userCursorPos);
  void createNewLineCharacter();
  void cleanTextBlock();
  void resetSuggestionIndex();
  void correctEnteredText(bool isSpaceAfter);
  void correctTextOnVSwipe();
  void nextSuggestion();
	void prevSuggestion();
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
  bool replacedSuggestion() const;
  
  int getLengthBeforePreviousUpdate() const;
  int getLengthDiff() const;
  int getVisibleLength() const;
  
  FLUnicodeString matchCase(const FLUnicodeString &word);
  
  void setMemo(std::shared_ptr<SplittageMemo> memo);
  std::shared_ptr<SplittageMemo> getMemo() const;
  
  // Functions for debug.
  void rememberContext(const std::vector<FLUnicodeString> &tokens) { context = tokens; }
  std::vector<FLUnicodeString> getContext() const { return context; }
  
private:
  FleksyListenerInterface &out;
	FLSuggestionsContainer *response;
	FLRequestDataHolder *request;
	int suggestionIndx;
	FLUnicodeString correctedText;
	bool isPunctuation;
  bool isSpaceAfterTextBlock;
  bool isExactEntry; // if typed the word accuratly
  bool isSymbolTextBlock;
  bool addedWordToDictionary;
  bool isUserSetCapitalization;
  bool userEditedText;
  bool changedToNextSuggestion;
  bool isAccuratelyTyped;
  bool isEmoji;
  
  void changeSuggestion(int offset);
  void prepareTextBlockToRecieveOrRemoveCharacters();
  
  void printTextBlock() const;
  void deleteSuggestions();
  
  int lengthBeforePreviousUpdate = 0;
  void setLengthBeforePreviousUpdate(int length);
  
  // Text blocks that were space broken and subsequently modified will carry information about
  // their life before being split apart to help with data collection.
  std::shared_ptr<SplittageMemo> _memo;
  
  // Data For debug.
  std::vector<FLUnicodeString> context;
};

#endif
