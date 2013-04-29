package utils;

public class Debugger {
	
	public static boolean internalDebug = false;
	public final static int MAX_LEVEL = Level.CONVERTING;
	
	public static class Level {
		public final static int INITIALIZE = 1;
		public final static int LOADING = 2;
		public final static int TESTING = 3;
		public final static int READING = 4;
		public final static int DEFINING = 5;
		public final static int CONVERTING = 6;
		public final static int PRINTING = 7;
	}
	
	public static void enableInternalDebugMode(boolean enable){
		internalDebug = enable;
	}
	
	public static boolean proceeding(final int NEXT_LEVEL){
		return (MAX_LEVEL >= NEXT_LEVEL || !internalDebug);
	}
	
}
