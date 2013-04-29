package utils;

public class Word {
	
	public String label = "";
	public String literal = "";
	public boolean punk = false;
	public boolean error = false;
	public boolean capper = false;
	public boolean known = false;
	
	public Word(String l, boolean p, boolean e){
		label = l;
		error = e;
		punk = p;
	}
	
	public void setLiteral(String l){
		literal = l;
	}
	
	public void setCaps(boolean c){
		capper = c;
	}
	
	public void setErr(boolean e){
		error = e;
	}
	
	public void setLabel(String l){
		label = l;
	}
	
	public void setKnown(boolean k){
		known = k;
	}
	
}
