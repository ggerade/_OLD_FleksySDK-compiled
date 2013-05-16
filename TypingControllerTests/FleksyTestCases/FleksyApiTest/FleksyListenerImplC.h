#ifndef __FleksySample1__FleksyListenerImplC__
#define __FleksySample1__FleksyListenerImplC__

#include "FleksyListenerInterface.h"

class FleksyListenerImplC: public FleksyListenerInterface{
public:
  FleksyListenerImplC();
  void onSetComposingText(const FLString text);
  void onSetComposingRegion(int start, int end);
  void onChangeSelection(int selectionStart, int selectionEnd);
  FLExternalEditorState onRequestEditorState();
  
  // below methods are optional:
  void onReceiveSuggestions(std::vector<FLString> suggestions, int selectedIndex);
  void onSelectedSuggestionChanged(int selectedIndex);
  //    void onSpeak(const FLString text);
      void onBeginBatchEdit();
      void onEndBatchEdit();
  //    void onCaseChanged(bool upperCase);
  //    void onDictionaryModified(FLDictionaryChangeEvent event, FLString word);
  //    void onMessageReceived(FLMessageType type, FLString message);
  //    void onRequestAdditionalSuggestions(const FLString rawText);
  
  
  /////Testing
  void TESTsetScreenText(std::string text);
  std::string getTextOnScreen();
  void TESTsetInitialCursorPosition(int position);
  int getComposingStart();
  int getComposingEnd();
  int getSuggestionIndex();
  FLString getSuggestionForIndex(int index);
  FLString getTextAroundCursor(int numOfCharsAroundCursor);
  int getSelectionStart();
  int getSelectionEnd();
  ///EOF Testing
  
private:
  FLExternalEditorState state;
  int composingEnd = 0;
  int composingStart = 0;
  int suggestionIndex;
  std::vector<FLString> displayedSuggestions;
};

#endif