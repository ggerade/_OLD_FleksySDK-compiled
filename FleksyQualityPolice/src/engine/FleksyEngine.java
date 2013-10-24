package engine;

import java.util.ArrayList;

import com.syntellia.fleksy.api.EngineLoader;
import com.syntellia.fleksy.api.FLEnums;
import com.syntellia.fleksy.api.FileUtils;
import com.syntellia.fleksy.api.FleksyAPI;

import utils.Client;
import utils.DataManager;
import utils.FleksyInterface;
import utils.Log;
import utils.Touch;

public class FleksyEngine {

	private final static String TAG = "FleksyEngine";
	
	public static FleksyAPI api;
	private static EngineLoader engineLoader;
	public static FleksyInterface cOutput;
	
	public static String rawTxt = "";
	private static String latestText = "";
	public static boolean upperCase = false;
	public static boolean sendingTaps = false;
	public static boolean useSuggestions = true;
	public static boolean endOfSuggestions = false;
	
	private static Client client;
	public static long timer = 0;
	public static String time = "";
	public static boolean online = false;
	private static boolean initialized = false;
	public static boolean externalDebug = false;
	
	public static void createEngine(boolean d) {
		if(!initialized){
			if(d){
				externalDebug = true;	
				loadEngine("Debug");
			}else{
				loadEngine("Release");
			}
			initialized = true;
		}
	}
	
	public static boolean connectServer(String IP){
		if(IP != null){
			connectToServer(IP);
		}
		return online;
	}
	
	public static void setLatestText(String text){
		//System.out.println("LastestText: " + text);
		latestText = text;
	}
	
	private static String cleanText(String input){
		return input.trim();
	}
	
	private static String cleanPunct(String input){
		return input.trim().substring(input.length()-1);
	}
	
	public static void initializeSuggestions(boolean android){
		if(online){
			String rawInput = rawTxt;
			try{
				String suggestions = client.getSuggestionsFor(rawInput);
				TestEngine.action = "Initializing Suggestions for " + rawInput + " which returned " + suggestions;
				if(android){ DataManager.parseSuggestions(suggestions); }
				if(useSuggestions){ api.setAdditionalSuggestions(rawInput, suggestions); }
			}catch (Exception e){
				Log.e(TAG, "Failed to Initialize Suggestions: " + e.getLocalizedMessage());
			}
		}
	}
	
	public static void recreateTapEvents(ArrayList<Touch> touches){
		if(online && sendingTaps){
			client.sendTapsToPhone(touches);
		}
	}
	
	public static void recreateTapEvent(String points){
		if(online && sendingTaps){
			client.tapOnceOnPhone(points);
		}
	}
	
	public static void recreateSwipe(String dir){
		if(online && sendingTaps){
			client.swipeOnPhone(dir);
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static void closeClient(){
		if(online){
			client.stop();
		}
	}
	
	private static void connectToServer(String IP){
		client = new Client(IP);
		while(client.connecting){
			Thread connect = new Thread(client);
			connect.run();
		}
	}
	
	public static void stopTimer(){
		timer = (System.currentTimeMillis() - timer)/1000;
		int mins = (int) (timer/60);
		int secs = (int) (timer - (mins*60));
		String breaker = ":";
		if(secs < 10){
			breaker += "0";
		}
		time = mins + breaker + secs;
	}
	
	private static void loadEngine(String version) {
		final String basePath = "../Android";
		try{
	    	api = new FleksyAPI();
		    cOutput = new FleksyInterface("../osx/lib/" + version + "/Fleksylib.dylib");
	        engineLoader = new EngineLoader();
	        
//	        File file = new File(basePath + "/FleksySDKResources/" + FileUtils.getResourceFileName("English")); //NON-FUNCTIONING CODE, NEEDS TO BE REBUILT
//	        RandomAccessFile stream = new RandomAccessFile(file, "rw"); //NON-FUNCTIONING CODE, NEEDS TO BE REBUILT
//	        FLFileDescriptor descriptor = new FLFileDescriptor(stream.getFD(), stream.getFilePointer(), file.length()); //NON-FUNCTIONING CODE, NEEDS TO BE REBUILT
	        engineLoader.loadEngineAsync(basePath + "/FleksySDKResources/encrypted/" + FileUtils.getJetResourceFileName("English"), api, true);
//			engineLoader.loadEngineAsync(descriptor, api, userWordList, true); //NON-FUNCTIONING CODE, NEEDS TO BE REBUILT
			
		    api.setActiveKeyboard(FLEnums.FLKeyboardID.FLKeyboardID_QWERTY_UPPER.ordinal(), false);
		    api.setCapitalizationMode(FLEnums.FLCapitalizationMode.FLCapitalizationMode_CAP_SENTENCES.ordinal());
            api.setPlatformKeyboardSize(320, 216);
		    api.startTypingSession(false);
		    
		}catch(Exception e){
	    	Log.e(TAG, "LoadEngine Failed : " + e.getLocalizedMessage());
	    	e.printStackTrace();
	    }
    }

	public static String getLatestText() {
		if(sendingTaps && online){
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			latestText = cleanText(client.getTextFromScreen());
		}
		return latestText;
	}
	
	public static String getLatestPunctuation(){
		if(sendingTaps && online){
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			latestText = cleanPunct(client.getTextFromScreen());
		}
		return latestText;
	}
	
}
