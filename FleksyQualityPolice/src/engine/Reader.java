package engine;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import utils.Log;

public class Reader {
	private final static String TAG = "Reader";
	
	private static BufferedReader reader;
	
	public String readFile(String location, String fileName, boolean newLines){
		StringBuilder output = new StringBuilder();
		TestEngine.action = "Reading textfile: " + fileName;
		try {
			reader = new BufferedReader(new InputStreamReader(new FileInputStream(location+fileName),"UTF-8"));
			String line;
			int lineNumber = 0;
			while((line = reader.readLine()) != null){
				lineNumber++;
				if(lineNumber > 1 && newLines){output.append(" ");}
				output.append(line);
			}
		} catch (Exception e) {
			Log.e(TAG, "Error Reading File: " + e.toString());
		}
		return output.toString();
	}
	
}
