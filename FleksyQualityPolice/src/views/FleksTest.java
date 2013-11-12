package views;

import java.util.Scanner;

import com.syntellia.fleksy.internal.api.FleksyPrivateAPI;

import utils.DataManager;
import utils.Debugger;
import utils.Log;

import engine.FleksyEngine;
import engine.TestEngine;

public class FleksTest {
	
	private static int n = 0;
	private static int e = 0;
	private static int s = 0;
	
	public static boolean print = true;
	private static boolean noisy = true;
	private static boolean shift = true;
	private static boolean errors = true;
	private static boolean debug = false;
	private static boolean client = true;
	public static boolean learn = false;
	public static boolean tapper = false;
	
	private final static String N = "n";
	private final static String E = "e";
	private final static String S = "s";
	private final static String G = "g";
	
	private final static String GOAL = "-g";
	private final static String DBUG = "-d";
	private final static String IBUG = "-b";
	private final static String XNOS = "-n";
	private final static String XERR = "-e";
	private final static String XSFT = "-s";
	private final static String ANDY = "-a";
	private final static String XOUT = "-o";
	private final static String LERN = "-l";
	private final static String TAPS = "-t";
	private final static String ACNT = "-a";
	private final static String TAP2 = "-tt";
	private final static String XSUG = "-ps";
	private final static String X_IP = "-ip";
	private final static String LRN2 = "-ll";
	private final static String EZCP = "-ez";
	
	private final static String STLW = "-tlw";
	private final static String SSLW = "-slw";
	private final static String SCLW = "-clw";
	private final static String SPLW = "-plw";
	private final static String LANG = "-loc:";
	
	public static String languageCode = "en-US";
	
	private static Scanner input;
	private final static int FAIL = 404;
	protected static TestEngine mainEngine;
	public final static float Version = 7.1f;
	private static boolean debugging = false;
	private final static String Alt = "7OMATO";
	
	private static FleksyPrivateAPI privateAPI;
	private static String [] myArgs;
	
	public static void main(String[] args){
		myArgs = args;
		initialOperations();
		if(Debugger.proceeding(Debugger.Level.INITIALIZE)){
			handleArguments(args);
			buildEngine();
		}
		System.exit(TestEngine.acurracyPass ? 0 : FAIL);
	}
	
	private static void initialOperations(){
		Debugger.enableInternalDebugMode(debugging);
		if(debugging){ Log.out("..::: Debugging Version " + Alt + " :::..\n");
		}else{ Log.out("..:: FleksyTester v" + Version + " ::..\n"); }
		Runtime.getRuntime().addShutdownHook(new Thread() {
			public void run(){
				if(!TestEngine.success){
					Log.err("NO SUCCESS HERE : FAILED\n");
					TestEngine.displayFailedMessage();
				}
			}
		});
	}
	
	private static void handlePostLoadArguments(){
		privateAPI = new FleksyPrivateAPI();
			for(int i = 0; i <  myArgs.length; i++){
			
				String a = myArgs[i];
				if(a.contains(STLW)){
					float weight = Float.parseFloat(myArgs[i + 1]);
					System.out.println("setSettingTransformLayerWeight(" + weight + ")");
					privateAPI.setSettingTransformLayerWeight(weight);
				}
				else if(a.contains(SSLW)){
					float weight = Float.parseFloat(myArgs[i + 1]);
					System.out.println("setSettingShapeLayerWeight(" + weight + ")");
					privateAPI.setSettingShapeLayerWeight(weight);
				}
				else if(a.contains(SCLW)){
					float weight = Float.parseFloat(myArgs[i + 1]);
					System.out.println("setSettingContextLayerWeight(" + weight + ")");
					privateAPI.setSettingContextLayerWeight(weight);
				}
				else if(a.contains(SPLW)){
					float weight = Float.parseFloat(myArgs[i + 1]);
					System.out.println("setSettingPlatformLayerWeight(" + weight + ")");
					privateAPI.setSettingPlatformLayerWeight(weight);
				}
			}
	}
	
	private static void handleArguments(String[] args){
		if(args.length < 1){ 
			awaitIPnum(null);
			return; 
		}
		for(String arg : args){
			
			String a = arg.toLowerCase();
			
			if(a.equals(DBUG)){ 		debug = true;
			
			}else if(a.equals(IBUG)){ 	FleksyEngine.externalDebug = true;
			
			}else if(a.equals(X_IP)){ 	client = false;
			
			}else if(a.equals(XNOS)){ 	noisy = false;
			
			}else if(a.equals(XERR)){ 	errors = false;
			
			}else if(a.equals(XSFT)){ 	shift = false;
			
			}else if(a.equals(ACNT)){	DataManager.noAccentsOnSecondCompare();
			
			}else if(a.equals(EZCP)){ 	DataManager.enableEasyCompare();
			
			}else if(a.equals(ANDY)){ 	DataManager.androidMode = true;
			
			}else if(a.equals(XOUT)){ 	print = false;
			
			}else if(a.equals(LRN2)){ 	learn = true;
			
			}else if(a.equals(GOAL)){ 	awaitGoal();
			
			}else if(a.equals(LERN)){ 	DataManager.enableLearning();
			
			}else if(a.equals(XSUG)){ 	FleksyEngine.useSuggestions = false;
			
			}else if(a.equals(TAP2)){ 	tapper = true;
			
			}else if(containsVal(a,N)){ n = getUserVal(a); noisy = false;
				
			}else if(containsVal(a,E)){ e = getUserVal(a); errors = false;
				
			}else if(containsVal(a,S)){ s = getUserVal(a); shift = false;
				
			}else if(arg.contains(LANG)){ 
				String lang = arg.replace(LANG, "");
				if(lang != null && !lang.isEmpty()){
					languageCode = lang;
				}
				else{
					Log.err("Bad Language! " + arg + " " + lang);
				}
				
			}else if(containsVal(a,G)){ DataManager.setDesiredGoal(getUserVal(a));
			
			}else if(a.equals(TAPS)){ 	FleksyEngine.sendingTaps = true; }
			
			
		}
		awaitIPnum(args[0]);
		
	}
	
	private static boolean containsVal(String input, String command){
		return ( input.substring(1).matches("[0-9]+") && input.startsWith(command) );
	}
	
	private static int getUserVal(String input){
		return (Integer.parseInt(input.substring(1)));
	}
	
	private static void buildEngine(){
		try{
			FleksyEngine.createEngine(debug, languageCode);
		}catch(Exception e){
			e.printStackTrace();
			Log.err("Loading Engine Failed! Testing Failed! Exiting Environment! Good Day Sir!\n");
			return;
		}
		
		handlePostLoadArguments();
		Log.out("Running LanguageCode: " + languageCode + "\n");
		mainEngine = new TestEngine(awaitNoise(), awaitError(), awaitShift(), (learn || tapper), languageCode);
		FleksyEngine.closeClient();
	}
	
	private static void awaitIPnum(String ip){
		if(!client){ return; }
		input = new Scanner(System.in);
		boolean connected = false;
		if(ip != null){
			if(!ip.contains("[a-zA-Z]+")){
				connected = FleksyEngine.connectServer(ip);
			}
		}
		while(!connected){
			Log.out("\nInsert server IP address (Or type 'Q' to skip): \n");
			ip = input.next();
			if(ip.toLowerCase().contains("q")){
				return;
			}
			connected = FleksyEngine.connectServer(ip);
		}
	}
	
	private static int awaitNoise(){
		if(!noisy){ return n; }
		int noise = -1;
		input = new Scanner(System.in);
		while(noise < 0){
			Log.out("\nInsert desired level of Noise : \n");
			if(input.hasNextInt()){
				noise = input.nextInt();
			}else{ input.next(); }
		}
		return noise;
	}
	
	private static int awaitError(){
		if(!errors){ 
			if(e > 10){ e = 10; }
			return e; 
		}
		int error = -1;
		input = new Scanner(System.in);
		while(error < 0 || error > 10){
			Log.out("\nInsert preferred level of Error (0 - 10) : \n");
			if(input.hasNextInt()){
				error = input.nextInt();
			}else{ input.next(); }
		}
		return error;
	}
	
	private static int awaitShift(){
		if(!shift){ return s; }
		int shifty = -1;
		input = new Scanner(System.in);
		while(shifty < 0){
			Log.out("\nInsert wanted level of Shift : \n");
			if(input.hasNextInt()){
				shifty = input.nextInt();
			}else{ input.next(); }
		}
		return shifty;
	}
	
	private static void awaitGoal(){
		int goalie = -1;
		input = new Scanner(System.in);
		while(goalie < 0 || goalie > 100){
			Log.out("\nInsert required accuracy (0 - 100) : \n");
			if(input.hasNextInt()){
				goalie = input.nextInt();
			}else{ input.next(); }
		}
		DataManager.setDesiredGoal(goalie);
	}

}
