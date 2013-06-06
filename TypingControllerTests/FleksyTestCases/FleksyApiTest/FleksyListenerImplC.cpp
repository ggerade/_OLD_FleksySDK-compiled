#include "FleksyListenerImplC.h"
#include <assert.h>

using namespace std;

FleksyListenerImplC::FleksyListenerImplC() {
  composingEnd = 0;
  composingStart = 0;
}

void FleksyListenerImplC::onSetComposingText(const FLString text){
  int n = composingEnd - composingStart;
  
  if(composingStart != composingEnd){
    //printf("Erasing from %i by %i\n", composingStart, n);
    state.text.erase(composingStart, n);
  }
  printf("Inserting at [%i, %i]\n", composingStart, composingEnd);
  state.text.insert(composingStart, text);
  
  //composingStart = composingEnd;
  
  printf("SCREEN:<%s> \n", state.text.c_str());
}

void FleksyListenerImplC::onSetComposingRegion(int start, int end){
  
  printf("onSetComposingRegion: start: %i, end: %i, text: <%s>\n", start, end, state.text.c_str());
  assert(start <= state.text.length() && start >= 0);
  assert(end <= state.text.length() && end >= 0);
  assert(end >= start);
  if(start < 0 || end < 0){
    printf("Start or end is negative! start: %i, end: %i", start, end);
    return;
  }
  composingStart = start;
  composingEnd = end;
}

void FleksyListenerImplC::onChangeSelection(int selectionStart, int selectionEnd){
  printf("onChangeSelection: start: %i, end: %i\n", selectionStart, selectionEnd);
  //composingStart = selectionStart;
  //composingEnd = selectionEnd;
  state.selectionEnd = selectionEnd;
  state.selectionStart = selectionStart;
}

FLExternalEditorState FleksyListenerImplC::onRequestEditorState(){
  printf("onRequestEditorState: text: %s, start: %i, end: %i\n", state.text.c_str(), state.selectionStart, state.selectionEnd);
  return state;
}
//////////////////Testing//////////////////////////////
void FleksyListenerImplC::TESTsetScreenText(string text){
    state.text = FLStringMake(text.c_str());
    TESTsetInitialCursorPosition((int)state.text.length());
}

void FleksyListenerImplC::TESTsetInitialCursorPosition(int position){
  state.selectionStart = position;
  state.selectionEnd = position;
}

string FleksyListenerImplC::getTextOnScreen(){
    return string((char*)state.text.c_str());
}

int FleksyListenerImplC::getComposingStart(){
  return composingStart;
}

int FleksyListenerImplC::getComposingEnd(){
  return composingEnd;
}

int FleksyListenerImplC::getSelectionStart(){
  return state.selectionStart;
}

int FleksyListenerImplC::getSelectionEnd(){
  return state.selectionEnd;
}

void FleksyListenerImplC::onReceiveSuggestions(vector<FLString> suggestions, int selectedIndex){
  displayedSuggestions = suggestions;
  suggestionIndex = selectedIndex;
}

void FleksyListenerImplC::onSelectedSuggestionChanged(int selectedIndex){
  suggestionIndex = selectedIndex;
}

int FleksyListenerImplC::getSuggestionIndex(){
  return suggestionIndex;
}

void FleksyListenerImplC::onBeginBatchEdit(){
  printf("onBeginBatchEdit()\n");
}

void FleksyListenerImplC::onEndBatchEdit(){
  printf("onEndBatchEdit()\n");
}

FLString FleksyListenerImplC::getSuggestionForIndex(int index){
  if(displayedSuggestions.size() == 0){return FLStringMake("");}
  return displayedSuggestions[index];
}

FLString FleksyListenerImplC::getTextAroundCursor(int numOfCharsAroundCursor){
  int buffer = 10;//10 chars buffer
  int start = composingEnd - (numOfCharsAroundCursor + buffer);
  if(start < 0){
    start = 0;
  }
  // printf("getTextAroundCursor() start: %i, end: %i", start, composingEnd + numOfCharsAroundCursor);
  return state.text.substr(start, composingEnd + numOfCharsAroundCursor + buffer);
}

