package com.chris.triangle;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;


public class GLRenderer implements Renderer {

	@Override
	public void onDrawFrame(GL10 arg0) {
		//onDrawFrame是负责对每一帧的绘制，这边我全部交给了GLLib这个类去做。
		// TODO Auto-generated method stub
		GLLib.draw();
	}

	@Override
	public void onSurfaceChanged(GL10 arg0, int width, int height) {	
		//onSurfaceChanged是Surface改变大小的时候调用的，这个时候我们可以去设置OpenGL的视觉区域大小。
		// TODO Auto-generated method stub
		Log.e("chris-magic" ,"before GLLib.init(width ,height)");
		GLLib.init(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 arg0, EGLConfig arg1) {
		//onSurfaceCreated是Surface创建的时候调用的。
		// TODO Auto-generated method stub
		
	}

}
