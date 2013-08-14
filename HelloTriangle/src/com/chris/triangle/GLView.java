package com.chris.triangle;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class GLView extends GLSurfaceView {
	private GLRenderer mRenderer;

	public GLView(Context context, AttributeSet attrs) {
		super(context, attrs);
		// TODO Auto-generated constructor stub
		init();
	}

	public GLView(Context context) {
		super(context);
		init();
	}

	private void init() {
		setEGLContextClientVersion(2); //设置EGL上下文的版本，这边选择2.0

		mRenderer = new GLRenderer();	
		setRenderer(mRenderer);			//设置粉刷器，也就是这边的GLRenderer

		// setRenderMode(RENDERMODE_WHEN_DIRTY);
		setRenderMode(RENDERMODE_CONTINUOUSLY);

	}
}
