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
  bool isPunctuationInside() const;
	void setIsPunctuationInside(bool isPunctuation);
  bool isSpaceEnabled() const;
  void setIsSpaceEnabled(bool isSpaceEnabled);
  bool isNewLineTextBlock() const;
  bool isSymbolsTextBlock() const;
  void setIsSymbolsTextBlock(bool symbol);
  bool isEmojiTextBlock() const;
  void setIsEmojiTextBlock(bool isEmoji);
  bool isEndSentence() const;
  bool isBeginSentence() const;
  bool isUserEditedText() const;
  void setIsAccuratelyTyped(bool isAccuratelyTyped);
  bool getIsAccuratelyTyped() const;
  
	FLRequestDataHolder *getRequest();
  FLUnicodeString getText() const;
  int getSuggestionIndex() const;
  void setSuggestionIndex(int suggIndex);
	bool getIsExactEntry() const;
  bool isCorrected() const;
  
  void addCharacter(FLPoint p, const FLUnicodeString &c, int index, FLKeyboardPtr &keyboard);
  void setSuggestions(const std::vector<FLUnicodeString>& suggestions);
  void setRequestPoints(const std::vector<FLPoint> &points);
	
	void deleteText();
  FLUnicodeString deleteCharacter(int indx);
  void createNewLineCharacter();
  void cleanTextBlock();
  void resetSuggestionIndex();
  void correctEnteredText(bool isSpaceAfter);
  void correctTextOnVSwipe();
  void nextSuggestion();
	void prevSuggestion();
  FLUnicodeString getTextToCorrect();
  
  void printSelf(int tbNumber) const;
  FLUnicodeString toLowerCase(const FLUnicodeString &string);
  
  bool containsNonAlphaCharacters(SystemsIntegrator* fleksy) const;
  bool containsApostrophe() const;
  bool isSplitWithSpace() const;
  void setUserCapitalization(bool isUserSet);
  bool userSetCapitalization() const;
  bool replacedSuggestion() const;
  
  int getLengthBeforePreviousUpdate() const;
  int getLengthDiff() const;
  
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
  FLUnicodeString matchCase(const FLUnicodeString &word);
  void prepareTextBlockToRecieveOrRemoveCharacters();
  
  void printTextBlock() const;
  void deleteSuggestions();
  
  
  int lengthBeforePreviousUpdate = 0;
  void setLengthBeforePreviousUpdate(int length);
};

#endif
