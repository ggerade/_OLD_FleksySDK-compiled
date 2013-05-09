FleksyAPI:

Interactions with the library are done via FleksyAPI and  FleksyListenerInterface.

Commands such as taps, deleting, adding space, changing suggestions etc. are sent to FleksyAPI to be processed.
FleksyListenerInterface is then called to inform of appropriate actions that should be performed in the text editor.

There are four required functions that have to be implemented in FleksyListenerInterface:
- void onSetComposingText(const FLString text) is called when there is new text that needs to be added to the text editor
- void onSetComposingRegion(int start, int end) is called when section of the text needs to be marked as composing
- void onChangeSelection(int selectionStart, int selectionEnd) is called when the selection has changed, cursor moved.
selectionStart and selectionEnd represent cursor in the text field. When selectionStart = selectionEnd indicates that cursor needs to be moved by the text editor to the location
of the selectionEnd. When selectionStart != selectionEnd indicates that the portion of the text between selectionStart and selectionEnd is being selected.
- FLExternalEditorState onRequestEditorState() - FLExternalEditorState contains information about current text in the text editor and cursor position.
On this call implementation needs to return FLExternalEditorState with any text present in the text editor and cursor state(position) in the text.

Example:
//Implement and create FleksyListenerInterface object
FleksyListenerImpl* listenerImpl = new FleksyListenerImpl();
//Create FleksyAPI object and pass in your FleksyListenerInterface implementation.
FleksyAPI api = new FleksyAPI(listenerImpl);
//Calling this will result in a call to onSetComposingText(const FLString text) with text = "h" in your FleksyListenerImpl;
api.sys->sendTap(195, 108);

onSetComposingRegion() and onSetComposingText():
These two functions work together to create text
onSetComposingRegion(startPos, endPos) sets the region of the text to be "composing". To the user usually this region
is presented as underlined or highlighted indicating that it's being edited right now. onSetComposingText() will override that 
region with the new text.

Program flow with FleksyAPI and FleksyListenerInterface calls when typing "Hello"
api->sendTap(195, 108);
onSetComposingRegion(start:0,end:0)
onSetComposingText("H")

api->sendTap(80, 36);
onSetComposingRegion(start:0,end:1)
onSetComposingText("He")

api->sendTap(300, 100);
onSetComposingRegion(start:0,end:2)
onSetComposingText("Hel")

api->sendTap(300, 100);
onSetComposingRegion(start:0,end:3)
onSetComposingText("Hell")

api->sendTap(270, 40);
onSetComposingRegion(start:0,end:4)
onSetComposingText("Hello")

api->space();
onSetComposingRegion(start:0,end:5)
onSetComposingText("Hello ") //Here our composing region is start:0,end:6, we don't want to have space in composing region
onSetComposingRegion(start:0,end:5)

----------------------------------------

Text Correction:

Text is corrected if FLCorrectionMode is set to FLCorrectionMode_ALWAYS (default mode).

After sending a few taps, calling api->space() will result in text being corrected to the first best prediction with the space after the corrected word.
Let's say after 5 taps text in the text editor is "hekko"
"hekko" -> api->space() -> "hello "
calling api->nextSuggestion() will replace current suggestion with the next best suggestion.
"hello " -> api->nextSuggestion() -> "jello " (this is just an example next suggestion could be different)
similarly calling api->previousSuggestion() will replace current suggestion with the previous one.
"jello " -> api->previousSuggestion() -> "hello "

----------------------------------------
