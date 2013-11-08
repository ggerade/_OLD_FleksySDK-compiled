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
  void setTextEntered(const FLUnicodeString &text);
  FLUnicodeString getTextEntered();
  void setLength(int length, const std::string &who);
  int getLength();
  bool isPunctuationInside();
	void setIsPunctuationInside(bool isPunctuation);
  bool isSpaceEnabled();
  void setIsSpaceEnabled(bool isSpaceEnabled);
  bool isNewLineTextBlock();
  void setIsNewLineTextBlock(bool isNewLine);
  bool isSymbolsTextBlock();
  void setIsSymbolsTextBlock(bool symbol);
  void setIsEndSentence(bool isEndSentence);
  bool isEndSentence();
  bool isUserEditedText();
  void setIsAccuratelyTyped(bool isAccuratelyTyped);
  bool getIsAccuratelyTyped();
  
	FLRequestDataHolder *getRequest();
  FLUnicodeString getText();
  int getSuggestionIndex();
  void setSuggestionIndex(int suggIndex);
	bool getIsExactEntry();
  bool isCorrected();
  
  void addCharacter(FLPoint p, const FLUnicodeString &c, int index, FLKeyboardPtr &keyboard);
  void setSuggestions(const std::vector<FLUnicodeString>& suggestions);
  void setRequestPoints(const std::vector<FLPoint> &points);
	
	void deleteText();
  FLUnicodeString deleteCharacter(int indx);
  void createNewLineCharacter();
  void cleanTextBlock();
  void resetSuggestionIndex();
  int correctEnteredText(bool isSpaceAfter);
  int correctTextOnVSwipe();
  int nextSuggestion();
	int prevSuggestion();
  FLUnicodeString getTextToCorrect();
  
  void printSelf(int tbNumber);
  FLUnicodeString toLowerCase(const FLUnicodeString &string);
  
  bool containsNonAlphaCharacters(SystemsIntegrator* fleksy);
  bool containsApostrophe();
  bool isSplitWithSpace();
  void setUserCapitalization(bool isUserSet);
  bool userSetCapitalization();
  bool replacedSuggestion();
  
private:
  FleksyListenerInterface &out;
	FLSuggestionsContainer *response;
	FLRequestDataHolder *request;
	int length;
	int suggestionIndx;
	FLUnicodeString correctedText;
	bool isPunctuation;
  bool isEndSentencePunc;
  bool isSpaceAfterTextBlock;
  bool isExactEntry; // if typed the word accuratly
  bool isNewLine;
  bool isSymbolTextBlock;
  bool addedWordToDictionary;
  bool isUserSetCapitalization;
  bool userEditedText;
  bool changedToNextSuggestion;
  bool isAccuratelyTyped;
  
  int changeSuggestion(int offset);
  FLUnicodeString capitalize(const FLUnicodeString &word);
  void prepareTextBlockToRecieveOrRemoveCharacters();
  
  void printTextBlock();
  void deleteSuggestions();
};

#endif
