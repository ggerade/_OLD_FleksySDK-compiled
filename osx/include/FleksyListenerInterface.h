//
//  FleksyListenerInterface.h
//  FleksySDK
//
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#ifndef __FleksySDK_FleksyListenerInterface_h__
#define __FleksySDK_FleksyListenerInterface_h__

#include <sstream>
#include <string>
#include <vector>
#include "FLEnums.h"
#include "FLUnicodeString.h"

struct FLExternalEditorState{
  FLUnicodeString text;
  int selectionStart = 0;
  int selectionEnd = 0;
  int composingStart = -1;
  int composingEnd = -1;
  
  FLUnicodeString displayString() const {
    std::stringstream ss;
    ss << "SCREEN: <" << text.c_str() << ">";
    ss << "[" << composingStart << "," << composingEnd << "] ";
    ss << "[" << selectionStart << "," << selectionEnd << "] ";
    return ss.str();
  }
};

class FleksyListenerInterface{
  
public:
  
  /*********Required*******************/
  /*
   * Commit text to the text editor and set the new cursor position to be after the inserted text
   */
  virtual void onSetComposingText(FLUnicodeString text) = 0;
  /*
   * Mark a certain region of text as composing text
   */
  virtual void onSetComposingRegion(int start, int end) = 0;
  /*
   * Request text editor to move cursor to some position in the text
   */
  virtual void onChangeSelection(int selectionStart, int selectionEnd) = 0;
  /*
   * Request editor state which includes full text that is currently in the editor and
   * selection of region. if selectionStart = selectionEnd, indicates cursor position
   * This is used to determine initial editor state
   */
  virtual FLExternalEditorState onRequestEditorState() = 0;
  
  /**************Optional************************/
  /*
   * Speaks the string using TTS.
   */
  virtual void onSpeak(FLUnicodeString text){};
  /*
   * Lets text editor know that there will be edits to the text after this call
   * editor should not send any updates until endBatchEdit() is called
   */
  virtual void onBeginBatchEdit(){};
  /*
   * Indicates the end of the edits to the text, text editor can now report
   * what changes has been made. ex: report new cursor position
   */
  virtual void onEndBatchEdit(){};
  /*
   * This is called when the case of character to follow is different the previous one.
   * This can be used for example to set the UI state of a shift button
   */
  virtual void onCaseChanged(bool upperCase){};
  /*
   * Called when the capitalization mode changes
   */
  virtual void onCapitalizationModeChanged(FLCapitalizationMode mode){};
  /*
   * Send message to the platform
   * FLMessageType_USER                       - some message user should see
   * FLMessageType_NO_NEXT_SUGGESTION         - reached end of the suggestion list
   * FLMessageType_NO_PREVIOUS_SUGGESTION     - reached beginning of the suggestion list
   * FLMessageType_SPACEBAR_STATE_PUNCTUATION - next spacebar press or swipe right will add punctuation
   * FLMessageType_SPACEBAR_STATE_CLEAR       - next spacebar press or swipe right will add space
   */
  virtual void onMessageReceived(FLMessageType type, FLUnicodeString message){};
  /*
   * FLDictionaryChangeEvent_ADDED   - word was added to the dictionary
   * FLDictionaryChangeEvent_REMOVED - word was removed from the dictionary
   */
  virtual void onDictionaryModified(FLDictionaryChangeEvent event, FLUnicodeString word){};
  /*
   * Ask platform for suggestions
   */
  virtual void onRequestAdditionalSuggestions(FLUnicodeString rawText){};
  /*
   * Send suggestion list to the platform to display(aka Candidates)
   * Suggestions could be empty. When suggestions list is empty, that means that there are no available suggestions and UI should update to indicate that there are no suggestions
   */
  virtual void onReceiveSuggestions(std::vector<FLUnicodeString> suggestions, int selectedIndex){};
  /*
   * Send an index of suggestion platform should display as current suggestion
   */
  virtual void onSelectedSuggestionChanged(int selectedIndex){};
  
  virtual ~FleksyListenerInterface(){};
};

#endif /* defined(__FleksySDK_FleksyListenerInterface_h__) */
