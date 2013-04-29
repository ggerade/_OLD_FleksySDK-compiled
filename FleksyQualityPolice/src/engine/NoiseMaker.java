package engine;

import java.util.ArrayList;
import java.util.Random;

import utils.Key;
import utils.Touch;

public class NoiseMaker { 
	@SuppressWarnings("unused")
	private final static String TAG = "NoiseMaker";
	
	@SuppressWarnings("unused")
	private static int width, height;
	private final static Random randomNse = new Random();
	private final static Random randomErr = new Random();
	private final static Random randomSft = new Random();
	private static boolean prepareShift = true;
	private final static int MAX_TAP_TIME = 60;
	private final static int MIN_TAP_TIME = 50;
	private final static float CHANCE = 90.0f;
	private final static int MIN_WORD_LN = 5;
	
	public static int TAP_NOISE = 0;
	public static int ERROR_LVL = 0;
	public static int SHIFT_LVL = 0;
	
	private static float sX = 0;
	private static float sY = 0;
	
	public static void initializeNoise(int w, int h, final int noise, final int error, final int shift){
		width = w;
		height = h;
		TAP_NOISE = noise;
		ERROR_LVL = error;
		SHIFT_LVL = shift;
		randomNse.setSeed(noise + error + shift);
		randomErr.setSeed(noise + error + shift);
		randomSft.setSeed(noise + error + shift);
	}
	
	public static Touch makeTap(Key key, long time, int indx){
		float x = key.x;
		float y = key.y;
		
		double radius = getNoiseDouble(TAP_NOISE);
		double angle = getNoiseDouble(Math.PI*2);
		
		x += Math.cos(angle)*radius;
		y += Math.sin(angle)*radius;

		return shiftTap(indx, x, y, time);
	}
	
	public static void prepareNextShift(){
		prepareShift = true;
	}
	
	private static Touch shiftTap(int indx, float x, float y, long time){
		if(SHIFT_LVL == 0){ return new Touch(indx, x, y, time); }
		if(prepareShift){
			prepareShift = false;
			double radius = getShiftDouble(SHIFT_LVL);
			double angle = getShiftDouble(Math.PI*2);
			sX = (float) (Math.cos(angle)*radius);
			sY = (float) (Math.sin(angle)*radius);
		}
		return new Touch(indx, (x+sX), (y+sY), time);
	}
	
	public static ArrayList<Touch> makeSpecial(Key key, ArrayList<Touch> output, long time, int indx, boolean state){
		
		return output;
	}
	
	public static ArrayList<Touch> makePunctuation(Key key, ArrayList<Touch> output, long time, int indx, boolean state){
		
		return output;
	}
	
	public static int incrementTapTime(){		
		return (int) ((Math.random() * MAX_TAP_TIME) + MIN_TAP_TIME);
	}
	
	private static double getShiftDouble(double shift){
		return (randomSft.nextDouble() * shift);
	}
	
	private static double getNoiseDouble(double noise){
		return (randomNse.nextDouble() * noise);
	}
	
	public static boolean errorMaker(String word){
		float length = word.length();
		if(length < MIN_WORD_LN){ return false; } //Five Letter Words Only
		
		double chance = ( (ERROR_LVL/CHANCE)*(length-(MIN_WORD_LN-1)) );
		
		return (chance > randomErr.nextDouble());
	}

	public static String makeBadWord(String word){
		
		int location = randomErr.nextInt(word.length()-1);
		StringBuilder newWord = new StringBuilder();

		if(randomErr.nextBoolean()){ //REMOVE
			for(int i = 0; i < word.length(); i++){
				if(i == location){
					if(Character.isUpperCase(word.charAt(i))){
						char[] stringArray = word.toCharArray();
						stringArray[i+1] = Character.toUpperCase(stringArray[i+1]);
						word = new String(stringArray);
					}
					continue;
				}
				newWord.append(word.charAt(i));
			}
		}else{ //ADD
			String extra = String.valueOf((char)(randomErr.nextInt(26) + 'a'));
			for(int i = 0; i < word.length(); i++){
				if(i == location){
					if(Character.isUpperCase(word.charAt(i))){
						char[] stringArray = word.toCharArray();
						stringArray[i] = Character.toLowerCase(stringArray[i]);
						word = new String(stringArray);
						extra = extra.toUpperCase();
					}
					newWord.append(extra);
				}
				newWord.append(word.charAt(i));
			}
		}
		return newWord.toString();
	}
	
}
