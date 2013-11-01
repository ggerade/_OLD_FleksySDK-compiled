#ifndef FLTEXTBLOCK_H
#define FLTEXTBLOCK_H

#include "FLSuggestionsContainer.h"
#include "FLRequestDataHolder.h"
#include "FLTextBlock.h"
#include "PatternRecognizer/Platform.h"
#include "FleksyListenerInterface.h"
#include "FLKeyboard.h"

class SystemsIntegrator;

class FLTextBlock{
public:
	FLTextBlock(FleksyListenerInterface &listener);
  ~FLTextBlock();
  
  //Getters/Setters
  FLSuggestionsContainer *getResponse();
  void setCorrectedText(FLString text);
  void setTextEntered(FLString text);
  FLString getTextEntered();
  void setLength(int length);
  void setUTF16Length(const unsigned char *utf8String);
  int getLength();
  size_t getUTF16Length();
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
  FLString getText();
  int getSuggestionIndex();
  void setSuggestionIndex(int suggIndex);
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
  FLString getTextToCorrect();
  
  void printSelf(int tbNumber);
  FLString toLowerCase(FLString string);
  
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
  size_t utf16Length;
	int suggestionIndx;
	FLString correctedText;
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
  FLString capitalize(FLString word);
  void prepareTextBlockToRecieveOrRemoveCharacters();
  
  void printTextBlock();
  void deleteSuggestions();
};



#endif
