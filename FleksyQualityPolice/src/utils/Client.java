package utils;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.ArrayList;

import engine.FleksyEngine;

public class Client implements Runnable{
	private final static String TAG = "Client";

	public boolean connecting = true;
	private final static int port = 8080; 
	private static String serverIP;
	private static Socket server;
	
	public Client(String IP){
		serverIP = IP;
	}
	
	@Override
	public void run() {
	    try {
	    	server = openSocket(serverIP, port);
	    } catch (Exception e) {
	    	FleksyEngine.online = false;
	    	DataManager.androidMode = false;
	    	Log.e(TAG, "Connecting to Server: " + e.getLocalizedMessage());
	    	Log.e(TAG, "IP Entered: " + serverIP + " connection failed.");
//	    	e.printStackTrace();
	    }
	    connecting = false;
	}
	
	private Socket openSocket(String server, int port) throws Exception{
		
		Socket socket = null;
		// create a socket with a timeout
		try {
			InetAddress inteAddress = InetAddress.getByName(server);
			SocketAddress socketAddress = new InetSocketAddress(inteAddress, port);
			// create a socket
			socket = new Socket();
  
			// this method will block no more than timeout ms.
			int timeoutInMs = 2*1000;   // 10 seconds
			socket.connect(socketAddress, timeoutInMs);
			FleksyEngine.online = true;
			Log.out("Connected To Server!\n");
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Opening Socket: " + e.getLocalizedMessage());
			throw new Exception();
//			e.printStackTrace();
		}
		return socket;
	}
  
	public String getSuggestionsFor(String word) throws Exception{
		
		//Sending word, hoping for suggestions in return
		String output = "";
		try {
			output = converseWithServer(word);
//			Log.i(TAG, "Result: " + output);
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Sending Word: " + e.getLocalizedMessage());
			e.printStackTrace();
		}
		if(output.equals(null)){
			throw new NullPointerException();
		}
		return output;
	}
	
	public void sendTouches(String touch){
		
		//Sending touches as STATE @ {X,Y} @ TIME
		try {
			talkToServer(touch);
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Sending Touches: " + e.getLocalizedMessage());
			e.printStackTrace();
		}
	}
	
	private void talkToServer(String message) {
		
		// write text to the socket
		try {
			DataOutputStream out = new DataOutputStream(server.getOutputStream());
			out.writeChars(message);
			out.flush();
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Talking: " + e.getLocalizedMessage());
			e.printStackTrace();
		}
		
	}
	
	public void sendTapsToPhone(ArrayList<Touch> tooches){
		String str = null;
		try {
			DataOutputStream out = new DataOutputStream(server.getOutputStream());
			StringBuilder sending = new StringBuilder();
			for(Touch t :  tooches){
				sending.append(t.printPoints());
			}
			out.writeBytes(sending.toString() + "\n");
			out.flush();
			//Log.d("Waiting for Taps " + sending.toString());
			BufferedReader in = new BufferedReader(new InputStreamReader(server.getInputStream()));
			str = in.readLine();
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Conversing: " + e.getLocalizedMessage() + "with String: " + str);
			e.printStackTrace();
		}
	}
	
	public void tapOnceOnPhone(String points){
		String str = null;
		try {
			DataOutputStream out = new DataOutputStream(server.getOutputStream());
			out.writeBytes(points + "\n");
			out.flush();
			//Log.d("Waiting for Taps " + sending.toString());
			BufferedReader in = new BufferedReader(new InputStreamReader(server.getInputStream()));
			str = in.readLine();
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Conversing: " + e.getLocalizedMessage() + "with String: " + str);
			e.printStackTrace();
		}
	}
	
	public void swipeOnPhone(String dir){
		String str = null;
		try {
			DataOutputStream out = new DataOutputStream(server.getOutputStream());
			out.writeBytes(dir + "\n");
			out.flush();
			//Log.d("Waiting for Swipe");
			BufferedReader in = new BufferedReader(new InputStreamReader(server.getInputStream()));
			str = in.readLine();
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Conversing: " + e.getLocalizedMessage() + "with String: " + str);
			e.printStackTrace();
		}
	}
	
	public String getTextFromScreen(){
		String str = null;
		try {
			String output = "F13K59";
			DataOutputStream out = new DataOutputStream(server.getOutputStream());
			out.writeBytes(output + "\n");
			out.flush();
			//Log.d("Waiting for Text");
			BufferedReader in = new BufferedReader(new InputStreamReader(server.getInputStream()));
			str = in.readLine();
			if(str.equals("F13K59")){ str = getTextFromScreen(); }
			//Log.d("Currently on screen: " + str);
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Conversing: " + e.getLocalizedMessage());
			e.printStackTrace();
		}
		return str;
	}
	
	private String converseWithServer(String word) {
		String str = null;
		try {
			// write text to the socket
			Log.d("Writing: " + word);
			DataOutputStream out = new DataOutputStream(server.getOutputStream());
			out.writeBytes(word + "\n");
			out.flush();

			// read text from the socket
			Log.d("Waiting on Suggestions for: " + word);
			BufferedReader in = new BufferedReader(new InputStreamReader(server.getInputStream()));
			str = in.readLine();
			Log.d("Returned Suggestions: " + str);
			// close the reader, and return the results as a String
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Conversing: " + e.getLocalizedMessage());
			e.printStackTrace();
		}
		return str;
	}
	
	public void stop(){
		try {
			server.close();
		} catch (Exception e) {
			FleksyEngine.online = false;
			DataManager.androidMode = false;
			Log.e(TAG, "Stopping: " + e.getLocalizedMessage());
			e.printStackTrace();
		}
	}
}
