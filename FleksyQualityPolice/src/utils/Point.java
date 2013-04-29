package utils;

public class Point {
	
	private int state;
	private float x;
	private float y;
	private long time;
	
	public Point(int s, float x, float y, long t){
		this.state = s;
		this.x = x;
		this.y = y;
		this.time = t;
	}
	
	public int getState(){
		return this.state;
	}
	
	public void setState(int s){
		this.state = s;
	}
	
	public float getX(){
		return this.x;
	}
	
	public float getY(){
		return this.y;
	}
	
	public long getTime(){
		return this.time;
	}
	
	public Point clone(){
		Point p = new Point(state, x, y, time);
		return p;
	}
	
	public String cleanPrint(){
		return(x + "," + y + ",");
	}
	
	public String print(){
		return(state + " @ {" + x + ", " + y + "} @ " + time + "\n");
	}
}
