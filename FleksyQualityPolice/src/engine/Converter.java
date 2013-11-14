package engine;

import java.util.ArrayList;
import java.util.Random;

import com.syntellia.fleksy.api.FLEnums;

import utils.DataManager;
import utils.Key;
import utils.Log;
import utils.Touch;

public class Converter {
	private final static String TAG = "Converter";
	
	private static int width;
	private static int height;

	private static Random random;
	public static int pointH, pointL;
	private final static int MOVE = 1;
	private final static int TAP_AIR = 50;
	private final static int SWIPE_AIR = 100;
	private final static double MAX_DEG = Math.PI/12; // 15 Degrees
	
	@SuppressWarnings("serial")
	class BooleanException extends Exception {
		public BooleanException() { super(); }
		public BooleanException(String message) { super(message); }
		public BooleanException(String message, Throwable cause) { super(message, cause); }
		public BooleanException(Throwable cause) { super(cause); }
	}
	
	public Converter(int w, int h, int noise, int error, int shift){
		width = w; 
		height = h;
		pointH = 20;
		pointL = 10;
		random = new Random();
		random.setSeed(noise+error+shift);
		NoiseMaker.initializeNoise(w, h, noise, error, shift);
	}
	
	public ArrayList<Touch> convertKeys(ArrayList<Key> input){
		ArrayList<Touch> output = new ArrayList<Touch>();
		long time = System.currentTimeMillis();
		FleksyEngine.timer = time;
		int indx = 0;
		boolean enteringText = false;
		for(int i = 0; i < input.size(); i++){
			if(TestEngine.failed){
				throw new RuntimeException("Engine Fail! Aborting Key Conversion!");
			}
			Key curr = input.get(i);
			if(curr.special){ 								//SPECIAL
				output = makeSpecial(curr, output, time, indx, enteringText);
				time = incrementTime(output, SWIPE_AIR);
				enteringText = false;
			}else if(curr.punctuation){ 					//PUNCTUATION
				output = makePunctuation(curr, output, time, indx, enteringText);
				time = incrementTime(output, SWIPE_AIR);
				enteringText = false;
			}else if(!curr.symbol){ 						//TAPPING
				Touch tap = NoiseMaker.makeTap(curr, time, indx);
				time += NoiseMaker.incrementTapTime();
				FleksyEngine.recreateTapEvent(tap.printPoints());
				output.add(tap);
				TestEngine.action = "Sending Tap " + tap.getDownX() + "," + tap.getDownY();
				FleksyEngine.api.sendTap(tap.getDownX(), tap.getDownY(), tap.getTime(), 0);
				
				enteringText = true;
			}
			indx = incrementIndex(output);
		}
		TestEngine.action = "Enter";
		FleksyEngine.api.enter(0); 	//ENTER SWIPE
		FleksyEngine.stopTimer();
		return output;
	}
	
	private int incrementIndex(ArrayList<Touch> output){
		return output.get(output.size()-1).id + 1;
	}
	
	private long incrementTime(ArrayList<Touch> output, int airTime){
		return output.get(output.size()-1).getTime() + airTime;
	}
	
	private ArrayList<Touch> makePunctuation(Key key, ArrayList<Touch> output, long time, int indx, boolean correcting){

		output = makeCorrectingSwipeRight(output, time, indx, correcting);
		time = incrementTime(output, SWIPE_AIR);
		indx = incrementIndex(output);
		output.add(makeSwipeRight(time, indx)); //SWIPE RIGHT
		
		while(!DataManager.isCurrentPunctuationCorrect()){
			if(FleksyEngine.endOfSuggestions){
				FleksyEngine.endOfSuggestions = false;
				Log.out("Unimplemented Manual Punctuation Handler/Failed to find correct punctuation: " + 
				DataManager.getCurrentPunctuation() + "\n");
				break;
			}
			indx++; time += SWIPE_AIR;
			output.add(makeSwipeDown(time, indx)); //SWIPE DOWN
		}

		return output;
	}
	
	private ArrayList<Touch> makeCorrectingSwipeRight(ArrayList<Touch> output, long time, int indx, boolean correcting){
		try {
			output = autoCorrect(output, time, indx, correcting);
		} catch (BooleanException e) {
			Log.err("EndofSuggestions TRUE before : " + DataManager.getComparisonMade() 
					+ " Index: " + DataManager.getWordIndex() + "  Local: " + e.getLocalizedMessage() + "\n");
			Log.quick("\n" + DataManager.getComparisonMade() + "\n");
			FleksyEngine.endOfSuggestions = false;
			DataManager.incrementSuggestionIndex();
		} finally {
			DataManager.prepareNextWord();
		}
		NoiseMaker.prepareNextShift();
		return output;
	}
	
	private ArrayList<Touch> makeSpecial(Key key, ArrayList<Touch> output, long time, int indx, boolean correcting){
		
		switch(key.stype){
		
		case 1: //Swipe Right (Fleksy Corrects Input)
			output = makeCorrectingSwipeRight(output, time, indx, correcting);
			break;
		case 2: //Swipe Left
			Log.e(TAG, "Special Not Implemented! " + key.stype);
			break;
		case 3: //Swipe Up
			Log.e(TAG, "Special Not Implemented! " + key.stype);
			break;
		case 4: //Swipe Down
			Log.e(TAG, "Special Not Implemented! " + key.stype);
			break;
		case 5: //Enter
			Log.e(TAG, "Special Not Implemented! " + key.stype);
			break;
		case 6: //Toggle
			Log.e(TAG, "Special Not Implemented! " + key.stype);
			break;
		case 7: //Shift
			output.add(makeShiftSwipe(time, indx));
			break;
		case 8: //Space
			Log.e(TAG, "Special Not Implemented! " + key.stype);
			//makeSpace(output, time, indx);
			break;
		default: //Fail
			Log.e(TAG, "Error while making Special: Special not found!");
			break;
		}
		
		return output;
	}
	
	private ArrayList<Touch> autoCorrect(ArrayList<Touch> output, long time, int indx, boolean correcting) throws BooleanException {
		if(!correcting){return output;}
		if(FleksyEngine.endOfSuggestions){ throw new BooleanException("true when should be false"); }
		DataManager.setEnteredText();
		output = settingSuggestions(output, time, indx, true); //SWIPE RIGHT
		while(!DataManager.isCurrentSuggestionCorrect(false)){ //SWIPE DOWN UNTIL CORRECT
			indx++; time += SWIPE_AIR;
			if(FleksyEngine.endOfSuggestions){
				FleksyEngine.endOfSuggestions = false;	
				output = failedWord(output, time, indx);
				return output;
			}
			DataManager.addLatestTextToSuggestions();
			DataManager.saveComparisonMade();
			DataManager.incrementSuggestionIndex();
			output.add(makeSwipeDown(time, indx)); //SWIPE DOWN
		}
		DataManager.addLatestTextToSuggestions();
		return output;
	}
	
	private ArrayList<Touch> settingSuggestions(ArrayList<Touch> output, long time, int indx, boolean android){
		FleksyEngine.initializeSuggestions(android);
		output.add(makeSwipeRight(time, indx)); //SWIPE RIGHT
		return output;
	}
	
	private ArrayList<Touch> failedWord(ArrayList<Touch> output, long time, int indx) {
		output.add(makeSwipeLeft(time, indx)); //SWIPE LEFT
		indx++; time += SWIPE_AIR;
		output = retypeAccurately(output, time, indx); //RETYPE WORD ACCURATELY THEN SWIPE RIGHT
		indx = incrementIndex(output); 
		time = incrementTime(output, SWIPE_AIR);
		if(!DataManager.isCurrentSuggestionCorrect(true)){ //CHECK IF FOUND 2ND TIME THROUGH
			output.add(makeSwipeUp(time, indx)); //SWIPE UP
			if(FleksyEngine.endOfSuggestions){
				Log.quick("\n" + DataManager.getComparisonMade() + "\n");
				Log.err("EndofSuggestions TRUE on SwipeUP : " + DataManager.getComparisonMade() 
						+ " Index: " + DataManager.getWordIndex() + " Resetting to FALSE\n");
				FleksyEngine.endOfSuggestions = false;
			}
		}
		return output;
	}
	
	private ArrayList<Touch> retypeAccurately(ArrayList<Touch> output, long time, int indx){
		for(Key key : Definer.redefineText(DataManager.getCleanedCurrentWord(), true, DataManager.dontShiftFirstLetter())){ //RETYPE WORD ACCURATELY
			if(key.symbol){
				FleksyEngine.recreateSwipe("#T");
				FleksyEngine.recreateSwipe("#S");
				FleksyEngine.api.setActiveKeyboard(FLEnums.FLKeyboardID.FLKeyboardID_SYMBOLS.ordinal(), false);
				Touch tap = new Touch(indx, key.x, key.y, time);
				TestEngine.action = "Sending Tap " + tap.getDownX() + "," + tap.getDownY();
				FleksyEngine.api.sendTap(tap.getDownX(), tap.getDownY(), tap.getTime(), 0);
				indx++; time += TAP_AIR;
				FleksyEngine.recreateTapEvent(tap.printPoints());
				output.add(tap);
				FleksyEngine.recreateSwipe("#T");
			}else if(key.special){
				output.add(makeShiftSwipe(time, indx));
			}else{
				Touch tap = new Touch(indx, key.x, key.y, time);
				TestEngine.action = "Sending Tap " + tap.getDownX() + "," + tap.getDownY();
				FleksyEngine.api.sendTap(tap.getDownX(), tap.getDownY(), tap.getTime(), 0);
				indx++; time += TAP_AIR;
				FleksyEngine.recreateTapEvent(tap.printPoints());
				output.add(tap);
			}
			FleksyEngine.api.setActiveKeyboard(FLEnums.FLKeyboardID.FLKeyboardID_QWERTY_UPPER.ordinal(), false);
		}
		
		output = settingSuggestions(output, time, indx, false); //SWIPE RIGHT
		return output;
	}
	
	@SuppressWarnings("unused")
	private void makeSpace(ArrayList<Touch> output, long time, int indx){
		output.add(makeSwipeRight(time, indx)); //SWIPE RIGHT
		indx++; time += SWIPE_AIR;
		output.add(makeSwipeUp(time, indx)); //SWIPE UP
	}
	
	private Touch makeShiftSwipe(long time, int indx){
		float length = random.nextInt((int)(height/1.5)-height/2) + height/2;
		int pointCount = random.nextInt(pointL-pointL/2) + pointL/2;
		float y = (height-length)/2.0f + length;
		float x = random.nextInt(width/6 - width/12) + width/12;
		double angle = MAX_DEG*random.nextDouble();
		float subY = length/pointCount;
		float subX = (float) (Math.tan(angle)*subY);
		if(random.nextBoolean()){
			subX = -subX;
		}
		Touch shift = new Touch(indx, x, y, time);
		for(int i = 0; i < pointCount; i++){
			x -= subX;
			y -= subY;
			shift.addPoint(MOVE, x, y, time);
		}
		TestEngine.action = "Shifting";
		FleksyEngine.api.toggleShift();
		FleksyEngine.recreateSwipe("#S");
		return shift;
	}
	
	private Touch makeSwipeRight(long time, int indx){
		float length = random.nextInt(width/5-width/11) + width/11;
		int pointCount = random.nextInt(pointH-pointL) + pointL;
		float x = (width-length)/2;
		float y = random.nextInt(height*2/3 - height/3) + height/3;
		double angle = MAX_DEG*random.nextDouble();
		float plusX = length/pointCount;
		float plusY = (float) (Math.tan(angle)*plusX);
		if(random.nextBoolean()){
			plusY = -plusY;
		}
		Touch swipeRight = new Touch(indx, x, y, time);
		for(int i = 0; i < pointCount; i++){
			x += plusX;
			y += plusY;
			swipeRight.addPoint(MOVE, x, y, time);
		}
		TestEngine.action = "Space";
		FleksyEngine.api.space(0);
		FleksyEngine.recreateSwipe("#R");
		return swipeRight;
	}
	
	private Touch makeSwipeLeft(long time, int indx){
		float length = random.nextInt(width/5-width/11) + width/11;
		int pointCount = random.nextInt(pointH-pointL) + pointL;
		float x = (width-length)/2;
		float y = random.nextInt(height*2/3 - height/3) + height/3;
		double angle = MAX_DEG*random.nextDouble();
		float plusX = length/pointCount + length;
		float plusY = (float) (Math.tan(angle)*plusX);
		if(random.nextBoolean()){
			plusY = -plusY;
		}
		Touch swipeLeft = new Touch(indx, x, y, time);
		for(int i = 0; i < pointCount; i++){
			x -= plusX;
			y -= plusY;
			swipeLeft.addPoint(MOVE, x, y, time);
		}
		TestEngine.action = "Make Backspace";
		FleksyEngine.api.backspace(10);
		FleksyEngine.recreateSwipe("#L");
		return swipeLeft;
	}
	
	private Touch makeSwipeUp(long time, int indx){
		float length = random.nextInt(height/3-height/10) + height/10;
		int pointCount = random.nextInt(pointL-pointL/2) + pointL/2;
		float y = (height-length)/2 + length;
		float x = random.nextInt(width*2/3 - width/3) + width/3;
		double angle = MAX_DEG*random.nextDouble();
		float subY = length/pointCount;
		float subX = (float) (Math.tan(angle)*subY);
		if(random.nextBoolean()){
			subX = -subX;
		}
		Touch swipeUp = new Touch(indx, x, y, time);
		for(int i = 0; i < pointCount; i++){
			x -= subX;
			y -= subY;
			swipeUp.addPoint(MOVE, x, y, time);
		}
		TestEngine.action = "Previous Suggestion";
		FleksyEngine.api.previousSuggestion(0);
		FleksyEngine.recreateSwipe("#U");
		return swipeUp;
	}
	
	private Touch makeSwipeDown(long time, int indx){
		float length = random.nextInt(height/5-height/10) + height/10;
		int pointCount = random.nextInt(pointL-pointL/2) + pointL/2;
		float y = (height-length)/2;
		float x = random.nextInt(width*2/3 - width/3) + width/3;
		double angle = MAX_DEG*random.nextDouble();
		float plusY = length/pointCount;
		float plusX = (float) (Math.tan(angle)*plusY);
		if(random.nextBoolean()){
			plusX = -plusX;
		}
		Touch swipeDown = new Touch(indx, x, y, time);
		for(int i = 0; i < pointCount; i++){
			x += plusX;
			y += plusY;
			swipeDown.addPoint(MOVE, x, y, time);
		}
		TestEngine.action = "Next Suggestion";
		FleksyEngine.api.nextSuggestion(0);
		FleksyEngine.recreateSwipe("#D");
		return swipeDown;
	}
	
}
