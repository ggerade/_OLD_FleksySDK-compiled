package utils;

import java.util.ArrayList;

public class Touch {
	
	public int id;
	private boolean editable = true;
	private ArrayList<Point> points;
	
	public Touch(int i, float downX, float downY, long time){
		this.id = i;
		this.points = new ArrayList<Point>();
		this.points.add(new Point(0,downX,downY,time));
	}
	
	public ArrayList<Point> getPoints(){
		return this.points;
	}
	
	public Point getFirstPoint(){
		return this.points.get(0);
	}
	
	public Point getLastPoint(){
		return this.points.get(points.size()-1);
	}
	
	public float getDownX(){
		return this.getFirstPoint().getX();
	}
	
	public float getDownY(){
		return this.getFirstPoint().getY();
	}
	
	public float getUpX(){
		return this.getLastPoint().getX();
	}
	
	public float getUpY(){
		return this.getLastPoint().getY();
	}
	
	public long getTime(){
		return getLastPoint().getTime();
	}
	
	public void addPoint(int state, float x, float y, long time){
		if(editable){ this.points.add(new Point(state, x, y, time)); }
	}
	
	public String printPoints(){
		StringBuilder output = new StringBuilder();
		for(Point p : points){
			output.append(p.cleanPrint());
		}
		return output.toString();
	}
}
