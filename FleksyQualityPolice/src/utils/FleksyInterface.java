package utils;


import com.syntellia.fleksy.api.FLEditorState;
import com.syntellia.fleksy.api.FLEnums;
import com.syntellia.fleksy.api.FleksyListenerInterface;

import engine.FleksyEngine;
import engine.TestEngine;

/*
 * Functions in this class are called from native C++
 * by FLOutputInterfaceImplJava.cpp
 */
public class FleksyInterface extends FleksyListenerInterface{
	
	public FleksyInterface(String library){
		super(System.getProperty("user.dir") + "/" + library, true);
	}

	@Override
	public void onSetComposingText(String text) { //CURRENT TEXT IN TEXTFIELD
		if(!text.trim().isEmpty()){
			FleksyEngine.setLatestText(text);
		}
	}

	@Override
	public void onSetComposingRegion(int start, int end) {}

	@Override
	public void onChangeSelection(int selectionStart, int selectionEnd) {}

	@Override
	public FLEditorState onRequestEditorState() { //SOME HACK VADIM MADE
		return new FLEditorState();
	}

	@Override
	public void onSpeak(String text) {}

	@Override
	public void onBeginBatchEdit() {}

	@Override
	public void onEndBatchEdit() {}

	@Override
	public void onCaseChanged(boolean upperCase) {
		FleksyEngine.upperCase = upperCase;
	}

	@Override
	public void onReceiveSuggestions(String[] suggestions, int selectedIndex) {
		FleksyEngine.currSugIndex = selectedIndex;
	}

	@Override
	public void onSelectedSuggestionChanged(int selectedIndex) {}

	@Override
	public void onMessageReceived(int type, String message) {
		
		if (type == FLEnums.FLMessageType.FLMessageType_NO_NEXT_SUGGESTION.ordinal()) { //DOWN
			FleksyEngine.endOfSuggestions = true;
		}else{ 
			Log.out("onMessageReceived: Type: " + type + " Message: " + message + "\n");
			if (type == FLEnums.FLMessageType.FLMessageType_NO_PREVIOUS_SUGGESTION.ordinal()) { //UP
				FleksyEngine.endOfSuggestions = true;
			}else if (type == FLEnums.FLMessageType.FLMessageType_ERROR.ordinal()){
				TestEngine.displayFailedMessage();
			}
		}
		
	}

	@Override
	public void onDictionaryModified(int event, String word) {
		try {
			throw new Exception("Dictionary Modified! Event: " + event + " Word: " + word + "\n");
		} catch (Exception e) {
			Log.err(e.getLocalizedMessage());
		}
	}
}