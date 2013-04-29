package utils;

public class Key {

	public String label = "";
	public float x;
	public float y;
	public int stype = 0;
	public boolean caps = false;
	public boolean symbol = false;
	public boolean special = false;
	public boolean punctuation = false;
	
	
	public Key(String l, float x, float y){
		this.label = l;
		this.x = x;
		this.y = y;
		Log.d(x + "," + y + " Label: " + l);
	}
	
	public void setSpecial(int type){
		this.special = true;
		this.stype = type;
	}
	
	public void setPunctuation(){
		this.punctuation = true;
		this.symbol = false;
		if(label.equals(".") || label.equals("?") || label.equals("!")){
			this.caps = true;
		}
	}
	
	public void setSymbol(){
		this.symbol = true;
	}
}
