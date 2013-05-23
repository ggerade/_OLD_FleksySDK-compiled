#ifndef FLRESPONSE_H
#define FLRESPONSE_H

#include <string>
#include <vector>
#include "PatternRecognizer/Platform.h"
#include "FLSocketsCommon.h"

class FLSuggestionsContainer{
  
public:
	FLSuggestionsContainer();
	void setSuggestions(std::vector<FLString> suggs);
	std::vector<FLString>& getSuggestions();
  void clearSuggestions();
  void insertSuggestion(int index, FLString suggestion);
  int getSuggestionCount();
  
private:
	std::vector<FLString> suggestions;
};

#endif
