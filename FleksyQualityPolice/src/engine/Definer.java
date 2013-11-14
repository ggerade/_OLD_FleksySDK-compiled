package engine;

import java.util.ArrayList;
import java.util.HashMap;

import com.syntellia.fleksy.api.FLEnums;
import com.syntellia.fleksy.api.FLKey;

import utils.DataManager;
import utils.Key;
import utils.Log;
import utils.Word;

public class Definer {
	private final static String TAG = "Definer";
	
	private static boolean caps = false;
	private static HashMap<String, Key> keyboard;
	private final static String cappers = ".!?";
	private final static String punctuation = ".,?!:;";
	
	private static Key swipeR;
	private static Key shift;
	
	private static int wordLimit = 0;
	private static boolean unknown = false;
	
	public Definer(int maxWords,boolean skipUnknown){
		wordLimit = maxWords-1;
		unknown = skipUnknown;
		TestEngine.action = "Creating Definer " + wordLimit;
		keyboard = new HashMap<String, Key>();
		try{
			Log.d("QWERTY");
			for(FLKey key : FleksyEngine.api.getKeymapForKeyboard(FLEnums.FLKeyboardID.FLKeyboardID_QWERTY_UPPER.ordinal(), true)){
				float x = key.x;
				float y = key.y;
				Log.d("key " + key.label);
				keyboard.put(key.label, new Key(key.label,x,y));
			}
			Log.d("Symbols");
			for(FLKey key : FleksyEngine.api.getKeymapForKeyboard(FLEnums.FLKeyboardID.FLKeyboardID_SYMBOLS.ordinal(), false)){
				float x = key.x;
				float y = key.y;
				Key k = new Key(key.label,x,y);
				k.setSymbol();
				keyboard.put(k.label,k);
			}
			createPunctuation();
		}catch(Exception e){
			Log.e(TAG, "Error while defining coordinates: " + e);
			e.printStackTrace();
		}
	}
	
	private void createPunctuation(){
		for (int p = 0; p < punctuation.length(); p++) {
			String label = String.valueOf(punctuation.charAt(p));
			Key key = keyboard.get(label);
			if (key != null) {
				Log.d("Punctuation: " + label);
				key.setPunctuation();
			}
		}
		Log.d("Custom");
		swipeR = new Key("r",0,0);
		swipeR.setSpecial(1);
		shift = new Key("s",0,0);
		shift.setSpecial(7);
	}
	
	private static boolean accurate = false;
	private static boolean autoLower = false;
	
	public static ArrayList<Key> redefineText(String text, boolean exact, boolean lowerFirst){
		accurate = exact;
		autoLower = lowerFirst;
		return defineText(text);
	}
	
	public static ArrayList<Key> defineText(String text){
		ArrayList<Key> keys = new ArrayList<Key>();
		TestEngine.action = "Defining text '" + text + "'\n Accurate?: " + accurate;
		try{
			String lines[] = text.split(System.getProperty("line.separator"));
			mainloop:
			for(String line : lines){
				String words[] = line.split("[\\s]|[/]");
				int index = -1;
				for(int w = 0; w < words.length; w++){
					Word word = checkWordQuality(words[w]);
					if(word == null){
					    Log.d("Skipping " + words[w]);
					    continue;
					}else if(!accurate){
						index ++;
						if(wordLimit > 0 && index > wordLimit){ break mainloop; }
						word.setLabel(removeBadApostrophes(word.label));
						Log.d("Compare New: " + word.label + " Old: " + words[w]);
						word.setErr(NoiseMaker.errorMaker(word.label.replace("-", "")));
						DataManager.addWord(removePunctuation(word),word.punk,word.
											error,word.label,containsCappers(word.label));
						word.setLabel(word.label.replace("-", ""));
					}
					keys = createKeys(keys, (word.error ? createErrWord(word) : word.label), index);
				}
			}
		}catch(Exception e){
			Log.e(TAG, "Error while defining text: " + e.getLocalizedMessage());
			e.printStackTrace();
		}
		if(!accurate){ 
			DataManager.displayWordCount(); 
		}
		accurate = false;
		Log.Key(TAG, keys);
		return keys;
	}
	
	private static ArrayList<Key> createKeys(ArrayList<Key> currentKeys, String currentWord, int w){
		boolean punct = false;
		ArrayList<Key> addKeys = new ArrayList<Key>();
		for(int l = 0; l < currentWord.length(); l++){
			String letter = String.valueOf(currentWord.charAt(l));
			Key key = keyboard.get(letter.toUpperCase());
			Log.d(key.label+caps);
			if(shiftCheck(l,w,key,letter) && !key.symbol){
				Log.d(key.label);
				addKeys.add(shift);
			}
			caps = key.caps;
			punct = key.punctuation;
			addKeys.add(key);
		}
		if(!accurate && !punct && !caps){ addKeys.add(swipeR); }
		for(Key add : addKeys){ currentKeys.add(add); }
		return currentKeys;
	}
	
	private static boolean containsCappers(String word){
		for(int c = 0; c < cappers.length(); c++){
			char caps = cappers.charAt(c);
			if(word.indexOf(caps) >= 0){
				return true;
			}
		}
		return false;
	}
	
	private static String removeBadApostrophes(String word){
		if(word.endsWith("'")){
			return word.substring(0, word.length()-1);
		}
		if(word.startsWith("'")){
			return word.substring(1, word.length());
		}
		return word;
	}
	
	private static String removePunctuation(Word word){
		if(word.punk){
			return word.label.substring(0, word.label.length()-1);
		}
		return word.label;
	}
	
	private static String createErrWord(Word word){
		String virgin = word.label;
		if(word.punk){
			virgin = virgin.substring(0,virgin.length()-1);
		}
		String dirty = NoiseMaker.makeBadWord(virgin);
		if(word.punk){
			dirty = dirty.concat(word.label.substring(word.label.length()-1));
		}
		return dirty;
	}
	
	private final static String DBL_PUNCT = "DBL_PUNCT";
	private final static String HAS_DIGIT = "HAD_DIGIT";
	private final static String NON_CHRCT = "UNKNOWN_";
	private final static String MLT_APOST = "MLT_APOST";
	private final static String BAD_DASHS = "BAD_DASHS";
	private final static String NON_LETTR = "NON_LETTR";
	private final static String NON_EXIST = "NOT_FOUND";
	
	private static Word checkWordQuality(String unclean){
		
		StringBuilder clean = new StringBuilder();
		char[] chars = unclean.toCharArray();
		
		boolean dash = false;
		boolean hasAlpha = false;
		boolean hasPunct = false;
		boolean apostrophe = false;
		
		for(int i = 0; i < chars.length; i++){
			if(hasPunct){ //Double Punctuation
				Log.d(unclean + " : Double Punctuation");
				DataManager.ignored(unclean,DBL_PUNCT);
				return null; 
			}
			char c = chars[i];
			if(Character.isDigit(c)){ //Contains Digit
				Log.d(unclean + " : Contains Digit");
				DataManager.ignored(unclean,HAS_DIGIT);
				return null; 
			}
			if(Character.isLetter(c)){ 
				if(keyboard.get(String.valueOf(c).toUpperCase()) == null){ //Non-Existant Character
					Log.d(unclean + " : Non-existant Character : " + c);
					DataManager.ignored(unclean,NON_CHRCT+c);
					return null; 
				}
				hasAlpha = true;
				clean.append(c);
			}else{
				switch(c){
				case '\'':
					if(apostrophe){ //Multiple Apostrophes
						Log.d(unclean + " : Multiple Apostrophes");
						DataManager.ignored(unclean,MLT_APOST);
						return null; 
					}
					apostrophe = true; 
					clean.append(c);
					break;
				case '-':
					if(dash || apostrophe){ //Unconventional Dash location
						Log.d(unclean + " : Unconventional Dash location");
						DataManager.ignored(unclean,BAD_DASHS);
						return null; 
					}
					dash = true;
					clean.append(c);
					break;
				default:
					if(i == chars.length-1 && punctuation.indexOf(c) >= 0){
						hasPunct = true;
						clean.append(c);
					}
					break;
				}
			}
		}
		
		if(!hasAlpha){ //No Letters Found
			Log.d(unclean + " : No Letters Found");
			DataManager.ignored(unclean,NON_LETTR);
			return null; 
		}
		if(unknown && !FleksyEngine.api.knowsWord(clean.toString())){ //Word Not Found
			Log.d(unclean + " : Unknown Word");
			DataManager.ignored(unclean,NON_EXIST);
			return null; 
		}
		
		return new Word(clean.toString(), hasPunct, false);
	}
	
	private static boolean shiftCheck(int l, int w, Key key, String letter){
		if(autoLower){
			Log.d("AutoLower");
			autoLower = false;
			return letter.equals(letter.toLowerCase());
		}
		if(accurate){
			return (letter.equals(letter.toUpperCase()));
		}else{
			return (((l == 0 && letter.equals(letter.toLowerCase()) && (caps || w == 0)) || 
					(letter.equals(letter.toUpperCase()) && !caps && !(l == 0 && w == 0))) 
					&& !key.punctuation); //Not Punctuation
		}
	}

}
