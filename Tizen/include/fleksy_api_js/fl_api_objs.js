function FLApiKey (character, x, y, order) {
    this.text = character;
    this.x = x;
    this.y = y;
    this.order = order;
}

function FLEditorState (text, selectionStart, selectionEnd) {
	this.text = text;
	this.selectionStart = selectionStart;
	this.selectionEnd = selectionEnd;
	
	this.getEditorText = function(){
		return this.text;
	};
	
	this.getSelectionStart = function(){
		return this.selectionStart;
	};
	
	this.getSelectionEnd = function(){
		return this.selectionEnd;
	};
}
