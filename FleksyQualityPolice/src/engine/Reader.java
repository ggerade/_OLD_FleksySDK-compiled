package engine;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import utils.Log;

public class Reader {
	private final static String TAG = "Reader";
	
	private static BufferedReader reader;
	
	public String readFile(String location, String fileName, boolean newLines){
		StringBuilder fileText = new StringBuilder();
		TestEngine.action = "Reading textfile: " + fileName;
		try {
			reader = new BufferedReader(new InputStreamReader(new FileInputStream(location+fileName),"UTF-8"));
			String line;
			int lineNumber = 0;
			while((line = reader.readLine()) != null){
				lineNumber++;
				if(lineNumber > 1 && newLines){fileText.append(" ");}
				fileText.append(line);
			}
		} catch (Exception e) {
			Log.e(TAG, "Error Reading File: " + e.toString());
		}
		String output = fileText.toString();
    output = output.replaceAll("[\u00ab\u00bb\u201c\u201d\u201e\u201f\u300e\u300f\u301d\u301e\u301f\ufe43\ufe44\uff02]", "\"");
    output = output.replaceAll("[\u0027\u2018\u2019\u201a\u201b\u2039\u203a\u300c\u300d\ufe41\ufe42\uff07\uff62\uff63]", "'");
		output = output.replaceAll("\u00AD",""); // Strip invisible soft-hyphens.
		output = output.replaceAll("[\u2010\u2011\u2012\u2013\u2014\u2015\u2E3A\u2E3B\uFE31\uFE32\uFE58\uFE63\uFF0D]","\u002D"); // Turn crazy hyphens in to a regular - hyphen.
		output = output.replaceAll("[\u00A0\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008\u2009\u200A\u202F\u205F\u3000]","\u0020"); // Turn crazy spaces in to regular space.
		return output;
	}
	
}
