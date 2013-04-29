package utils;

import java.util.ArrayList;

import engine.FleksyEngine;

public class Log {
	
	private final static String border = " :: ";
	
	private static boolean print(){
		return (FleksyEngine.externalDebug || Debugger.internalDebug);
	}
	
	public static void out(String message){
		System.err.print(message);
	}
	
	public static void err(String message){
		System.err.print("ERR :: " + message);
	}
	
	public static void d(String message){
		if(print()){ System.out.println(message); }
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
