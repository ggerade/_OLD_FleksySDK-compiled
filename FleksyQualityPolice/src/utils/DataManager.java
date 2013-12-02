package utils;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import com.syntellia.fleksy.api.FLEnums;
import engine.FleksyEngine;
import engine.NoiseMaker;
import engine.TestEngine;

public class DataManager {
	@SuppressWarnings("unused")
	private final static String TAG = "DataManager";
	
	public static boolean androidMode = false;
	
	private static int min = 0;
	private static int goal = 0;
	private static int index = 0;
	private static int andex = 0;
	private static int marker = 0;
	private static int ignore = 0;
	private static int unknown = 0;
	private static int wordIndex = 0;
	private static float totalIndex = 0;
	@SuppressWarnings("unused")
	private static float totalAndex = 0;
	private static String lastComparison = "NONE";
	private final static int LIMIT = 26;
	private static boolean failed = false;
	private static boolean aFound = false;
	private static boolean noSugs = false;
	private static boolean ezComp = false;
	private static boolean learning = false;
	private static boolean dontAdd = false;
	private static String enteredText = "";
	private static float[] andyGraph = new float[30];
	private static float[] indexGraph = new float[30];
	private static List<Word> words = new ArrayList<Word>();
	private static StringBuilder data = new StringBuilder();
	private static StringBuilder knownMiss = new StringBuilder();
	private static StringBuilder unKnoMiss = new StringBuilder();
	private static StringBuilder output = new StringBuilder();
	private static StringBuilder ignored = new StringBuilder();
	private static StringBuilder indxGraph = new StringBuilder();
	private static StringBuilder andxGraph = new StringBuilder();
	private static StringBuilder accuGraph = new StringBuilder();
	private static StringBuilder comparisons = new StringBuilder();
	private static List<String> suggestions = new ArrayList<String>();
	private static List<String> androidSugs = new ArrayList<String>();
	private static HashMap<String, Pair> badWords = new HashMap<String, Pair>();
	
	public static void refresh(){
		refreshObjects();
		refreshNumbers();
		refreshGraphs();
	}
	
	private static void refreshNumbers(){
		min = 0;
		index = 0;
		andex = 0;
		marker = 0;
		ignore = 0;
		unknown = 0;
		wordIndex = 0;
		totalIndex = 0;
	}
	
	private static void refreshObjects(){
		words.clear();
		enteredText = "";
		data.setLength(0);
		suggestions.clear();
		output.setLength(0);
		ignored.setLength(0);
		unKnoMiss.setLength(0);
		knownMiss.setLength(0);
		comparisons.setLength(0);
		badWords.clear();
	}
	
	private static void refreshGraphs(){
		for(int i = 0; i < indexGraph.length; i++){
			indexGraph[i] = 0;
		}
		for(int i = 0; i < andyGraph.length; i++){
			andyGraph[i] = 0;
		}
		indxGraph.setLength(0);
		andxGraph.setLength(0);
		accuGraph.setLength(0);
	}
	
	public static void ignored(String unclean, String reason){
		final StringBuilder clean = new StringBuilder();
		for(char c : unclean.toCharArray()){
			if(Character.isLetter(c)){	
				clean.append(c);
			}
		}
		if(clean.toString().isEmpty()){return;}
		ignore++;
		ignored.append(" - " + clean.toString() + " " + reason + "\n");
	}
	
	public static void staticDictionary(){
		dontAdd = true;
	}
	
	public static void enableEasyCompare(){
		ezComp = true;
	}
	
	public static void enableLearning(){
		learning = true;
	}
	
	public static void setDesiredGoal(int g){
		if(g > 100){
			g = 100;
		}
		goal = g;
	}
	
	public static int getTargetGoal(){
		return goal;
	}
	
	public static void addWord(String l, boolean p, boolean e, String lit, boolean caps){
		boolean known = FleksyEngine.api.knowsWord(l);
		Log.d("Clean/Dirty : " + l + " / " + lit +" : hasPunct " + p + " hasErrs " + e + " hasCaps " + caps);
		if(learning && !known){
			FleksyEngine.api.addWordToDictionary(l);
		}
		Word word = new Word(l,p,e);
		word.setLiteral(lit);
		word.setKnown(known);
		word.setCaps(caps);
		words.add(word);
	}
	
	public static void displayWordCount(){
		Log.out("Total # of Words: " + words.size() + "\n");
	}
	
	public static void setEnteredText(){
		enteredText = FleksyEngine.getLatestText().trim();
	}
	
	public static void parseSuggestions(String sugs){
		if(!androidMode){return;}
		andex = 0;
		if(sugs.trim().length() > 0){
			aFound = false;
			noSugs = false;
			androidSugs = Arrays.asList(sugs.split(","));
			for(;andex < androidSugs.size(); andex++){
				if(androidSugs.get(andex).equals(words.get(wordIndex).label)){
					aFound = true;
					break;
				}
			}
			if(andex > 0){
				float increment = 1.0f/(andex+1.0f);
				totalAndex += increment;
			}
		}else{
			aFound = FleksyEngine.getLatestText().equals(words.get(wordIndex).label);
			noSugs = true;
		}
		if(aFound){
			andyGraph[andex]++;
		}else{
			andyGraph[andyGraph.length-1]++;
		}

	}
	
	public static void prepareNextWord(){
		String currword = "";
		if(index > 0 && wordIndex < words.size()){
			String old = "";
			String prev = "";
			if(wordIndex > 1){ old = words.get(wordIndex-2).literal; }
			if(wordIndex > 0){ prev = words.get(wordIndex-1).literal; }
			if(failed){
				String tab = " [ ] ";
				if(words.get(wordIndex).error){
					tab = " [E] ";
				}
				if(words.get(wordIndex).known){
					knownMiss.append(tab + words.get(wordIndex).label + "\n"); 
				}else{
					unknown++;
					unKnoMiss.append(tab + words.get(wordIndex).label + "\n"); 
				}
			}
			if(failed && suggestions.size() < 2){data.append("############################EPIC#FAIL###############################\n");}
			currword = words.get(wordIndex).label;
			data.append("Current Word '" + currword + "' ----------: WORD# " + (wordIndex+1) + " :-----------\n");
			data.append("Context: '" + old + " " + prev + " " + words.get(wordIndex).literal + "'\n");
			data.append("Entered Text: '" + enteredText + "' \nErroneous Taps: " + words.get(wordIndex).error + "\n.:Suggestions:.\n");
			if(androidMode){
				int max = ( suggestions.size() > androidSugs.size() ? suggestions.size() : androidSugs.size() );
				for(int i = 0; i < max; i++){
					if(i < suggestions.size()){
						data.append(" :F: " + suggestions.get(i) + "\t");
					}else{
						data.append("\t\t\t");
					}
					if(i < androidSugs.size() && !noSugs){
						data.append(" :A: " + androidSugs.get(i) + "\n");
					}else{
						data.append("\n");
					}
				}
			}else{
				for(String suggestion : suggestions){
					data.append(" - " + suggestion + "\n");
				}
			}

		}
		checkIndexRange(wordIndex);
		wordIndex++;
		printLoading();
		incrementAverageIndex(currword);
	}
	
	private static void printLoading(){
		float percent = (wordIndex * 1.0f/words.size()*1.0f)*100;
		if(percent > min && words.size() > 100){
			min ++;
			if(percent > marker){
				Log.quick("|");
				Log.out("\n" + marker + "% Processed\n");
				marker += 10;
			}else{
				Log.out("|");
			}
		}
	}
	
	private static void incrementAverageIndex(String currword){
		float increment = 0;
		if(!failed){
			if(index < LIMIT){
				indexGraph[index]++;
			}else{
				indexGraph[indexGraph.length-1]++;
			}
			increment = 1.0f/(index+1.0f);
			totalIndex += increment;
		}
		if(index > 0){
			if(androidMode){
				if(aFound){
					data.append("ANDROID_INDEX: " + andex + "\n");
				}else{
					data.append("ANDROID_INDEX: MAXED OUT\n");
				}
			}
			if(badWords.containsKey(currword)){
				Pair update = badWords.remove(currword);
				update.increment();
				update.addConflict(currConflict);
				badWords.put(currword, update);
			}else{
				Pair baddie = new Pair(1,currword);
				baddie.addConflict(currConflict);
				badWords.put(currword,baddie);
			}
			currConflict = null;
			if(failed){
				indexGraph[indexGraph.length-1]++;
				data.append("FLEKSY_INDEX: MAXED OUT\n");
				data.append("FAILED FINDING WORD! ADDING ZERO TO TOTAL_INDEX = " + totalIndex + " ]\n");
			}else{
				data.append("FLEKSY_INDEX: " + index + "\n");
				data.append("[ ( 1 / (" + index + " + 1) ) = " + increment + " += TOTAL_INDEX = " + totalIndex + " ]\n");
			}
			data.append("AVG_INDEX(WORD#/TOTAL_IDX): " + (wordIndex/totalIndex) + "\n\n");
			index = 0;
		}
		aFound = false;
		failed = false;
		suggestions.clear();
	}
	
	private static class Pair implements Comparable<Pair>{
		
		private int count;
		private String word;
		private HashMap<String, Pair> conflicts;
		
		public Pair(int c, String w){
			count = c;
			word = w;
			conflicts = new HashMap<String, Pair>();
		}

		public void addConflict(String con){
			if (conflicts.containsKey(con)) {
				Pair update = conflicts.remove(con);
				update.increment();
				conflicts.put(con, update);
			} else {
				conflicts.put(con, new Pair(1, con));
			}
		}
		
		public String sortConflicts(){
			StringBuilder build = new StringBuilder();
			ArrayList<Pair> sorted = new ArrayList<Pair>();
			for(Pair con : conflicts.values()){
				sorted.add(con);
			}
			Collections.sort(sorted);
			build.append(" < ");
			for(int i = 0; i < sorted.size() && i < 5; i++){
				Pair p = sorted.get(i);
				build.append(p.word + ":" + p.count + " ");
			}
			build.append(">");
			return build.toString();
		}
		
		public void increment(){
			count++;
		}

		@Override
		public int compareTo(Pair o) {
			return count < o.count ? 1 : count > o.count ? -1 : 0;
		}

	}
	
	private static String makeBar(String index, float amount){
		StringBuilder bar = new StringBuilder();
		bar.append(index + ": ");
		for(int i = 0; i < amount; i++){
			if(amount < (i+1)){
				bar.append("[");
			}else{
				bar.append("[]");
			}
		}
		bar.append(" " + amount*10 + "%\n");
		return bar.toString();
	}
	
	private static void createHeader(){
		float bestPercent = (indexGraph[0]/words.size())*100;
		Log.quick(" " + bestPercent + "% ] " + ignore + " ignored, " + unknown + " unknown, ");
		String header = "[AvgIndex: " + (words.size()/totalIndex) + 
				" ]\n[Index-0: " + bestPercent +
				"% ]\n[Index-1: " + (indexGraph[1]/words.size())*100 +
				"% ]\n[Index-2: " + (indexGraph[2]/words.size())*100 +
				"% ]\n[Ignored Words: " + ignore +  
				" ]\n[Unknown Words: " + unknown +  
				" ]\n[Processed Words: " + words.size() +
				" ]\n[Noise LVL: " + NoiseMaker.TAP_NOISE + 
				" ]\n[Error LVL: " + NoiseMaker.ERROR_LVL + 
				" ]\n[Shift LVL: " + NoiseMaker.SHIFT_LVL +
				" ]\n[Unknown in Dictionary: " + learning +
				" ]\n[Server Connected: " + FleksyEngine.online + 
				" ]\n[Platform Suggestions: " + (FleksyEngine.online && FleksyEngine.useSuggestions) +
				" ]\n[Debug Mode: " + (FleksyEngine.externalDebug || Debugger.internalDebug) + 
				" ]\n[Time Taken: " + FleksyEngine.time + " ]\n";
		Log.out(header);
		output.append(header);
	}
	
	private static void createBody(){
		output.append( 	"\n--==[ INDEX GRAPH ]==--\n" +
						indxGraph.toString() + 
						"\n--==[ ACCUMULATIVE GRAPH ]==--\n" +
						accuGraph.toString() + 
						"\n--==[ FAILED WORDS ]==--\n" +
						"\n.:::KNOWN WORDS:::.\n" +
						knownMiss.toString() +
						"\n.::" + unknown + " UNKNOWN WORDS::.\n" +
						unKnoMiss.toString() +
						"\n--==[ DATA ]==--\n" +
						data.toString() + 
						"\n--==[ " + ignore + " IGNORED WORDS ]==--\n" +
						ignored.toString() + 
						"\n--==[ COMPARED WORDS ]==--\n" +
						comparisons.toString() +
						"\n--==[ MISSED COUNT ]==--\n" +
						printBadWords().toString());
	}
	
	private static String printBadWords(){
		StringBuilder builder = new StringBuilder();
		List<Pair> words = new ArrayList<Pair>();
		for(Pair pair : badWords.values()){
			words.add(pair);
		}
		Collections.sort(words);
		for(Pair word : words){
			builder.append(word.word + " : " + word.count + word.sortConflicts() + "\n");
		}
		return builder.toString();
	}
	
	private static void makeGraphs(){
		float total = 0;
		indxGraph.append("INDEX LEVEL : PERCENTAGE HIT\n");
		accuGraph.append("CUMULATIVE IDX : PERCENTAGE HIT\n");
		andxGraph.append("\n--==[ ANDROID GRAPH ]==--\nINDEX LEVEL : PERCENTAGE HIT\n");
		for(int i = 0; i < LIMIT; i++){
			float percent = (indexGraph[i]/words.size())*10;
			indxGraph.append(makeBar(i + "\t",percent));
			float aPercent = (andyGraph[i]/words.size()*10);
			andxGraph.append(makeBar(i + "\t",aPercent));
			total += percent;
			accuGraph.append(makeBar(i + "\t", total));
		}
		float failure = (indexGraph[indexGraph.length-1]/words.size())*10;
		indxGraph.append(makeBar("FAIL", failure));
		andxGraph.append(makeBar("FAIL",(andyGraph[andyGraph.length-1]/words.size())*10));
		total += failure;
		accuGraph.append(makeBar("FAIL", Math.round(total)));
		if(androidMode){
			indxGraph.append(andxGraph.toString());
		}
	}
	
	public static void addWordToDictionary(){
		if(!dontAdd){
			boolean lowerCase = isPreviousCapper();
			String addMe = words.get(wordIndex).label;
			if (lowerCase) {
				char c[] = addMe.toCharArray();
				c[0] = Character.toLowerCase(c[0]);
				addMe = new String(c);
			}
			Log.d("Added to dictionary " + addMe + " Success? " 
			+ (FleksyEngine.api.addWordToDictionary(addMe) == 
			FLEnums.FLDictionaryChangeResult.FLDictionaryChangeResult_SUCCESS.ordinal()) + "\n");
		}
	}
	
	private static String currConflict;
	
	public static boolean isCurrentSuggestionCorrect(boolean firstSuggestion, boolean secondCheck){
		if(checkIndexRange(wordIndex) || FleksyEngine.endOfSuggestions){
			failed = true;
			return false;
		}
		String word = words.get(wordIndex).label;
		boolean err = words.get(wordIndex).error;
		String out = FleksyEngine.getLatestText();
		word = word.replaceAll("[-]", "").trim();
		out = out.replaceAll("[-]", "").trim();
		if(ezComp){
			word = word.replaceAll("[']", "").trim();
			out = out.replaceAll("[']", "").trim();
			word = word.toLowerCase();
			out = out.toLowerCase();
		}
		if(firstSuggestion && !word.equals(out)){
			currConflict = out;
		}
		if(secondCheck){ Log.d("Accurate Comparison: FLEKSY: " + out + " WORD: " + word + " ERR: " + err); }
		lastComparison = "INPUT: " + out + " XPECT: " + word;
		return word.equals(out) || (secondCheck && dontAdd);
	}
	
	public static void incrementSuggestionIndex(){ index++; }
	
	private static boolean checkIndexRange(int check){
		if(check >= words.size()){
			Log.err("Word Index Out Of Range: INDX: " + wordIndex + " MAX: " + words.size() + "\n");
			Log.quick(" I ");
			return true;
		}
		return false;
	}
	
	public static String getCleanedCurrentWord(){
		if(checkIndexRange(wordIndex)){
			return words.get(words.size()-1).label;
		}
		String word = words.get(wordIndex).label.replaceAll("[-]", "").trim();
		if(wordIndex < 1){ //Remove caps from the first letter of first word
			word = Character.toLowerCase(word.charAt(0)) + (word.length() > 1 ? word.substring(1) : "");
		}
		Log.d("Retyping: " + word);
		return word;
	}
	
	public static int getWordIndex(){
		return wordIndex;
	}
	
	public static String getComparisonMade(){ return lastComparison; }
	
	public static void saveComparisonMade(){
		if(checkIndexRange(wordIndex)){ return; }
		comparisons.append("Entered: " + FleksyEngine.getLatestText().replaceAll("[-]", "").trim() 
				+ " Comparing To: " + words.get(wordIndex).label.replaceAll("[-]", "").trim() + "\n");
	}
	
	public static void addLatestTextToSuggestions(){
		suggestions.add(FleksyEngine.getLatestText());
	}
	
	public static String getFailedDetails(){
		if(words != null){
			return ("Latest Text: " + getComparisonMade());
		}
		return "NO DETAILS";
	}
	
	public static String printOutData(){
		try{
			createHeader();
			makeGraphs();
			createBody();
		}catch(Exception e){
			e.getLocalizedMessage();
			Log.err(" Printing what we can.");
			Log.quick("\nPRINT FAIL\n");
		}
		return (output.toString());
	}
	
	public static void accuracyCheck(){
		if((indexGraph[0]/words.size())*100 < goal){
			TestEngine.acurracyPass = false;
		}
	}

	public static boolean isPreviousCapper() {
		if( wordIndex == 0 || checkIndexRange(wordIndex-1)){
			return false;
		}
		Log.d("PrevWord: " + words.get(wordIndex-1).literal);
		return words.get(wordIndex-1).capper;
	}

	public static boolean isCurrentPunctuationCorrect() {
		if( wordIndex == 0 || checkIndexRange(wordIndex-1)){
			return false;
		}
		if(words.get(wordIndex-1).punk){
			String prevWord = words.get(wordIndex-1).literal;
			return (FleksyEngine.getLatestPunctuation().startsWith(prevWord.substring(prevWord.length()-1)));
		}else{
			Log.err("Unnecessary Punctuation Check! What are you doing Grey? At: " + words.get(wordIndex-1).literal + "\n");
			Log.quick("\nPUNCT FAIL\n");
			return false;
		}
	}
	
	public static String getCurrentPunctuation(){
		if( wordIndex == 0 || checkIndexRange(wordIndex-1)){
			return null;
		}
		if(words.get(wordIndex-1).punk){
			String prevWord = words.get(wordIndex-1).literal;
			return prevWord.substring(prevWord.length()-1);
		}else{
			Log.err("Unnecessary Punctuation Get! Way to go Grey. At: " + words.get(wordIndex-1).literal + "\n");
			Log.quick("\nEPIC PUNCT FAIL\n");
			return null;
		}
	}
	
}
