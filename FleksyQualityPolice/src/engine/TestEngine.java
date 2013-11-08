package engine;

import java.io.File;
import java.io.PrintStream;
import java.util.ArrayList;
import utils.DataManager;
import utils.Debugger;
import utils.Key;
import utils.Log;
import utils.Touch;
import views.FleksTest;

public class TestEngine {
	
	private final static String TAG = "TestEngine";
	
	class TxtFile {
    	public String location;
    	public String fileName;
    	
    	public TxtFile(String l, String f){
    		this.location = l;
    		this.fileName = f;
    	}
    }
	
	public static boolean acurracyPass = true;
	public static boolean success = false;
	public static String currentFile = "";
	public static String action = "";
	public static String state = "";
	public static Reader reader;
	public static Definer definer;
	public static Converter converter;
	public static boolean failed = false;
	private final static String TestPath = "Assets/";
	private static ArrayList<TxtFile> tests = new ArrayList<TxtFile>();
	
	public TestEngine(int noise, int error, int shift, boolean encore, String languageCode){
		if(Debugger.proceeding(Debugger.Level.LOADING)){
			loadTests(TestPath + languageCode + "/");
			if(failed){ return; }
			reader = new Reader();
			definer = new Definer();
			converter = new Converter(320, 216, noise, error, shift);
			runEngine();
			if(encore){
				if(FleksTest.learn){ DataManager.enableLearning(); }
				if(FleksTest.tapper){ FleksyEngine.sendingTaps = true; }
				runEngine();
			}
		}
	}
	
	public static String readFile(String location, String fileName, boolean newLine){
		if(Debugger.proceeding(Debugger.Level.READING)){
			state = "ReadFile";
			return( reader.readFile(location,fileName,newLine) );
		}else{
			return null;
		}

	}
	
	@SuppressWarnings("static-access")
	public static ArrayList<Key> defineText(String text){
		if(Debugger.proceeding(Debugger.Level.DEFINING)){
			state = "DefineText";
			return( definer.defineText(text) );
		}else{
			return null;
		}
	}
	
	public static ArrayList<Touch> convertKeys(ArrayList<Key> input){
		if(Debugger.proceeding(Debugger.Level.CONVERTING)){
			state = "ConvertKeys";
			return( converter.convertKeys(input) );
		}else{
			return null;
		}
		
	}
	
	public static void runEngine() {
		if(Debugger.proceeding(Debugger.Level.TESTING)){
			if(tests.size() < 1){
				Log.err("There are no tests to run!");
				return;
			}
			runTests();
		}
		if(!failed){ success = true; }
	}
	
	private static void runTests(){
		for(TxtFile test : tests){
			currentFile = test.fileName;
			Log.out("Running Test: " + currentFile + "\n");
			Log.out("N:" + NoiseMaker.TAP_NOISE +  " E:" + NoiseMaker.ERROR_LVL + " S:" + NoiseMaker.SHIFT_LVL);
			if(DataManager.getTargetGoal() > 0){
				Log.out(" G:" + DataManager.getTargetGoal());
			}
			Log.out("\n");
			try{
				convertKeys(defineText(readFile(test.location,currentFile,true)));
				Log.out("\nDing! Dinner's ready!\n");
			}catch(Exception e){
				displayFailedMessage();
				Log.err("LocalMsg: " + e.getLocalizedMessage() + "\nStackTrace: ");
				e.printStackTrace();
			}
			DataManager.accuracyCheck();
			if(Debugger.proceeding(Debugger.Level.PRINTING) && FleksTest.print){
				printOutText();
			}
			DataManager.refresh();
		}
	}
	
	public static void displayFailedMessage(){
		Log.err("Testing failed in the " + state + " State while performing: " + action 
				+ "\nConverter Details: " + DataManager.getFailedDetails() + "\n");
		failed = true;
	}
	
	public static void printOutText(){
    	StringBuilder fileName = new StringBuilder();
    	fileName.append(System.currentTimeMillis()
    			+ "v" + (int)(FleksTest.Version*10)
    			+ "o" + (FleksyEngine.online ? 1 : 0)
    			+ "d" + (FleksyEngine.externalDebug ? 1 : 0)
    			+ "n" + NoiseMaker.TAP_NOISE 
    			+ "e" + NoiseMaker.ERROR_LVL
    			+ "s" + NoiseMaker.SHIFT_LVL
    			+ "g" + DataManager.getTargetGoal());
    	Log.out("Creating Output File...\n");
		try{
			PrintStream out = new PrintStream(new File("Output/" + fileName.toString() + ".txt"));
			if(failed){
				out.println("##############################################FAILED#TEST##############################################");
				out.println("Message:\tTesting failed in the " + state + " State \n\tWhile performing: " + action + "\n\tConverter Details: " + DataManager.getFailedDetails());
			}
			out.println("[Version # " + FleksTest.Version + " ] [Test File: "+ currentFile + " ]\n" + DataManager.printOutData());
			out.close();
			Log.out("Output sent to file: " + fileName.toString() + ".txt\n");
		}catch(Exception e){
			Log.e(TAG, "Creating Output file Failed! " + e.getLocalizedMessage());
			e.printStackTrace();
		}
	}
	
	private void loadTests(String path){
		File folder = new File(path);
		File[] listOfFiles = folder.listFiles();

		if(listOfFiles == null){
			failed = true;
			Log.e(TAG, "No Files Detected! Closing Tester.");
			return;
		}
	    for (File file : listOfFiles) {
	      if (file.isFile()) {
	    	  if(file.getName().contains("txt")){
	    		  tests.add(new TxtFile(path,file.getName()));
	    	  }
	      } else if (file.isDirectory()) {
	    	  loadTests(path + file.getName() + "/");
	      }
	    }
	}
	
}
