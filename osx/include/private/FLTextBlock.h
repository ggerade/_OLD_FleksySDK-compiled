#ifndef FLTEXTBLOCK_H
#define FLTEXTBLOCK_H

#include "FLSuggestionsContainer.h"
#include "FLRequestDataHolder.h"
#include "FLTextBlock.h"
#include "PatternRecognizer/Platform.h"
#include "FleksyListenerInterface.h"
#include "FLKeyboard.h"

class FLTextBlock{
public:
	FLTextBlock(FleksyListenerInterface &listener);
  
  //Getters/Setters
	void setResponse(FLSuggestionsContainer resp);
  FLSuggestionsContainer getResponse();
  void setCorrectedText(FLString text);
  //FLString getCorrectedText();
  void setTextEntered(FLString text);
  FLString getTextEntered();
  void setLength(int length);
  int getLength();
  bool isPunctuationInside();
	void setIsPunctuationInside(bool isPunctuation);
  bool isSpaceEnabled();
  void setIsSpaceEnabledBoolOnly(bool isSpaceEnabled);
  bool isNewLineTextBlock();
  void setIsNewLineTextBlock(bool isNewLine);
  bool isSymbolsTextBlock();
  void setIsSymbolsTextBlock(bool symbol);
  void setIsEndSentence(bool isEndSentence);
  bool isEndSentence();
  
	FLRequestDataHolder getRequest();
  FLString getText();
  int getSuggestionIndex();
	bool getIsExactEntry();
  bool isCorrected();
  
  void addCharacter(FLPoint p, FLChar c, int index, FLKeyboardPtr &keyboard);
  void setSuggestions(std::vector<FLString>& suggestions);
  void setRequestPoints(std::vector<FLPoint> points);
	
	void deleteText();
	FLChar deleteCharacter(int indx);
  void createNewLineCharacter();
  void cleanTextBlock();
  void resetSuggestionIndex();
  int correctEnteredText(bool isSpaceAfter);
  int correctTextOnVSwipe();
  int nextSuggestion();
	int prevSuggestion();
  
  void printSelf(int tbNumber);
  
private:
  FleksyListenerInterface &out;
	FLSuggestionsContainer response;
	FLRequestDataHolder request;
	int length;
	int suggestionIndx;
	FLString correctedText;
	bool isPunctuation;
  bool isEndSentencePunc;
  bool isSpaceAfterTextBlock;
  bool isExactEntry; // if typed the word accuratly
  bool isNewLine;
  bool isSymbolTextBlock;
  bool addedWordToDictionary;
  
  int changeSuggestion(int offset);
  FLString capitalize(FLString word);
  FLString toLowerCase(FLString string);
  FLString getTextToCorrect();
  void printTextBlock();
  void deleteSuggestions();
};



#endif
