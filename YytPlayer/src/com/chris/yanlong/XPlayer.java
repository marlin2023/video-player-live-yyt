package com.chris.yanlong;

public class XPlayer {
	static {
		System.loadLibrary("xplayer");
	}
	
	private native int initVideoPlayer(String filename);
	
	private native int play(int handle);
	
	private native int stopVideoPlayer(int handle);
	
	public int initVideo(String filename){
		return initVideoPlayer(filename);
	}
	
	public void xplayerPlay(int handle){
		play(handle);
	}
	
	public void xplayerStop(int handle){
		stopVideoPlayer(handle);
	}	
	
	//______________________________
	//-------------opengl
	private native void initOpenGL();
	
	private native void openGLResize(int screen_width ,int screen_height ,int display_w ,int display_h);
	private native void openGLRend();
	
	public  void openglInit(){
		initOpenGL();
	}
	
	public void openglResize(int screen_width ,int screen_height ,int display_w ,int display_h){
		openGLResize(screen_width ,screen_height ,display_w ,display_h);
	}
	public void openglRend(){
		openGLRend();
	}
	
	private CallBackFun call;
	
	public void initCall(CallBackFun call){
		this.call = call;
	}
	
	public void onPrepare(){
//		call.onPrepare(obj, errormsg)
		call.onPrepare();
	}
	
	public void onError(int errorCode){
		call.onError(errorCode);
	}
	
	//interface
	public interface CallBackFun{
		//1:onPrepare callback function
		public void onPrepare();
		
		//2:onError callback function		
		public void onError(int errorId);
		

	}
}
