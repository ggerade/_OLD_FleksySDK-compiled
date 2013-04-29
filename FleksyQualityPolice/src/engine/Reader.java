package engine;

import java.io.BufferedReader;
import java.io.FileReader;
import utils.Log;

public class Reader {
	private final static String TAG = "Reader";
	
	private static BufferedReader reader;
	
	public String readFile(String location, String fileName, boolean newLines){
		String output = "";
		TestEngine.action = "Reading textfile: " + fileName;
		try {
			reader = new BufferedReader(new FileReader(location+fileName));
			String line;
			int lineNumber = 0;
			while((line = reader.readLine()) != null){
				lineNumber++;
				if(lineNumber > 1 && newLines){output += " ";}
				output += line;
			}
		} catch (Exception e) {
			Log.e(TAG, "Error Reading File: " + e.toString());
		}
		return output;
	}
	
}
