package utils;

import java.util.ArrayList;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

import engine.FleksyEngine;

public class Log {
	
	public static boolean quickmode = false;
	private final static String border = " :: ";
	
	private static boolean print(){
		return (FleksyEngine.externalDebug || Debugger.internalDebug);
	}
	
	public static void quick(String message) {
		if(quickmode){
			try {
				new PrintStream(System.err, true, "UTF-8").print(message);
			} catch (UnsupportedEncodingException x) {
			}
		}
	}
	
	public static void out(String message) {
		if(quickmode){ return; }
		try {
			new PrintStream(System.err, true, "UTF-8").print(message);
		} catch (UnsupportedEncodingException x) {
		}
	}
	
	public static void err(String message){
		if(quickmode){ 
			quick("!"); 
			return;
		}
		try {
			new PrintStream(System.err, true, "UTF-8").print(message);
		} catch (UnsupportedEncodingException x) {
		}
	}
	
	public static void d(String message){
		if(quickmode){ return; }
		if (print()) {
			try {
				new PrintStream(System.err, true, "UTF-8").print(message);
			} catch (UnsupportedEncodingException x) {
			}
		}
	}
	
	public static void e(String TAG, String message){
		Log.err(TAG + border + message);
	}
	
	public static void String(String TAG, ArrayList<String> words){
		if(print()){
			Log.out(TAG + border);
			for(String word : words){ Log.out(word + " "); }
			Log.out("\n");
		}
	}
	
	public static void Key(String TAG, ArrayList<Key> keys){
		if(print()){
			Log.out(TAG + border);
			for(Key k : keys){ Log.out(k.label); }
			Log.out("\n");
		}
	}
	
	public static void Touch(ArrayList<Touch> touches){
		for(Touch t : touches){ Log.Point(t.getPoints()); }
	}
	
	public static void Point(ArrayList<Point> points){
		for(Point p : points){ Log.d(p.print()); }
	}
	
}
