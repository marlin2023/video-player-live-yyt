package com.chris.triangle;

public class GLLib {
	static {
		  System.loadLibrary("gljni");
		 }
		 
		 public static native void init(int width, int height);
		 
		 public static native void draw();
}
