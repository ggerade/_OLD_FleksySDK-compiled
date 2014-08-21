
function FleksyListenerImpl(){

this.onSetComposingText = function (text){
	flog("onSetComposingText() " + text);
};

this.onSetComposingRegion = function(start, end){
	flog("onSetComposingRegion() " + start + ":" + end);
};

this.onChangeSelection = function(selectionStart, selectionEnd) {
	flog("onChangeSelection() " + selectionStart + ":" + selectionEnd);
};

this.onBeginBatchEdit = function() {
	flog("onBeginBatchEdit()");
};

this.onEndBatchEdit = function() {
	flog("onEndBatchEdit()");
};

this.onCaseChanged = function(upperCase) {
	flog("onChaseChanged() " + upperCase);
};

this.onReceiveSuggestions = function(suggestions, selectedIndex, type) {
	flog("onReceiveSuggestions()" + " selIndx: " + selectedIndex + " type: " + type);
//	if(type == FLSuggestionsType_enum.FLSuggestionsType_PUNCTUATION){
//		flog("Punctuation! yay!");
//	}
//	for(var i = 0; i < suggestions.length; i++){
//		flog("<" + suggestions[i] + ">");
//	}
};

this.onSelectedSuggestionChanged = function(selectedIndex) {
	flog("onSelectedSuggestionChanged() " + selectedIndex);
};

this.onMessageReceived = function(type, message) {
	flog("onMessageReceived()");
};

this.onRequestEditorState = function() {
	flog("onRequestEditorState()");
	return new FLEditorState("Test state", 1, 2); //TODO:FIXTHIS
};

this.onDictionaryModified = function(event, word) {
	flog("onDictionaryModified()");
	
};

this.onCapitalizationModeChanged = function(mode) {
	flog("onCapitalizationModeChanged()");
};

this.onChangeKeyboardLayout = function(keyboardID) {
	flog("onChangeKeyboardLayout()");
};

}


var fleksyListenerJS = new FleksyListenerImpl();


