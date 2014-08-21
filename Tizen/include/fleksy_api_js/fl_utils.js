function t0HexString(character){
	var hex, j;
	var str = character;
	var hexRep = "";
	for (j=0; j<str.length; j++) {
	  hex = str.charCodeAt(j).toString(16);
	  hexRep += ("000"+hex).slice(-4);
	}
	return hexRep;
}

function toUnicodeString(character) {
	  var unicodeString = '';
	  for (var i=0; i < character.length; i++) {
	    var theUnicode = character.charCodeAt(i).toString(16).toUpperCase();
	    while (theUnicode.length < 4) {
	      theUnicode = '0' + theUnicode;
	    }
	    theUnicode = '\\u' + theUnicode;
	    unicodeString += theUnicode;
	  }
	  return unicodeString;
}

// \\u7937984\u34004 format
function toDisplayString(unicodechar){
	var x = character;
	var r = /\\u([\d\w]{4})/gi;
	x = x.replace(r, function (match, grp) {
	    return String.fromCharCode(parseInt(grp, 16)); } );
	x = unescape(x);
	return x;
}