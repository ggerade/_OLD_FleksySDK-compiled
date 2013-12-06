#ifndef FLRESPONSE_H
#define FLRESPONSE_H

#include <string>
#include <vector>
#include "PatternRecognizer/Platform.h"
#include "FLSocketsCommon.h"
#include "FLUnicodeString.h"

class FLSuggestionsContainer{
  
public:
	FLSuggestionsContainer();
	void setSuggestions(const std::vector<FLUnicodeString> &suggs);
	std::vector<FLUnicodeString> getSuggestions();
  void clearSuggestions();
  void insertSuggestion(int index, const FLUnicodeString &suggestion);
  int getSuggestionCount();
  
private:
	std::vector<FLUnicodeString> suggestions;
};

#endif
