#ifndef FLRESPONSE_H
#define FLRESPONSE_H

#include <string>
#include <vector>
#include "PatternRecognizer/Platform.h"
#include "FLUnicodeString.h"

class FLSuggestionsContainer{
  
public:
  FLSuggestionsContainer();
  void setSuggestions(const std::vector<FLUnicodeString> &suggs);
  void clearSuggestions();
  void insertSuggestion(int index, const FLUnicodeString &suggestion);
  
  std::vector<FLUnicodeString> getSuggestions() const;
  int getSuggestionCount() const;
  
private:
  std::vector<FLUnicodeString> suggestions;
};

#endif
