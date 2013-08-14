
package com.chris.yanlong;

import android.app.Activity;
import android.content.Context;
import android.content.res.Configuration;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.util.Log;
import android.widget.RelativeLayout;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.chris.yanlong.XPlayer.CallBackFun;

public class MainActivity extends Activity {
	
    public int media_handle = 0;

    public XPlayer xPlayer;

    private int display_width = 0;

    private int display_height = 0;

    private RelativeLayout layout;

    private GlBufferView glBufferView;

    private WakeLock m_wklk;
    
    private int player_stop_mark = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initDip2px(MainActivity.this);

        layout = (RelativeLayout) findViewById(R.id.rl_viewObj);
        playVideoSize();
    }

    @Override
    protected void onPause() {
        Log.e("chris_magic", "onPause");
        super.onPause();
        yyPlayerStop(media_handle);
        //player_stop_mark
        Log.e("chris_magic", "onPause ,after yyPlayerStop");
        if (null != m_wklk) {
            m_wklk.release();
            m_wklk = null;
        }
        Log.e("chris_magic", "onPause ,before glBufferView.onPause() ");
        glBufferView.onPause();	//BLOCK IN HERE
        Log.e("chris_magic", "onPause ,after glBufferView.onPause() ");
        layout.removeView(glBufferView);
        glBufferView = null;
        Log.e("chris_magic", "onPause ,in the end ");
    }

    @Override
    protected void onStop() {
        Log.e("chris_magic", "onStop");
        super.onStop();
    }

    @Override
    protected void onResume() {
        Log.e("chris_magic", "onResume");
        super.onResume();
        PowerManager pm = (PowerManager) getSystemService(POWER_SERVICE);
        m_wklk = pm.newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK, "yyt");
        m_wklk.acquire();
//        yyPlayerInit("http://hlscc.yinyuetai.com/stream/test20130719_1/prog_index.m3u8");
       int ret =  yyPlayerInit("http://hlscc.yinyuetai.com/stream/71511210000/prog_index.m3u8");
//        yyPlayerInit("/sdcard/video/ruyan.mp4");
//        yyPlayerInit("/sdcard/video/fangkaiai.mp4");
        
//        yyPlayerInit("http://192.168.1.89:9090/ruyan/test.m3u8");
       if(ret < 0){
    	   Log.e("chris" ,".................................");
    	   try {
			Thread.sleep(1000000000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
       }
       
        int smallH = screen_width * screen_width / screen_height;
        yyPlayerPlay(screen_width, smallH);
        layout.addView(glBufferView);
    }

    @Override
    protected void onStart() {
        Log.e("chris_magic", "onStart");
        super.onStart();
    }

    @Override
    protected void onDestroy() {
        Log.e("chris_magic", "onDestroy");
        super.onDestroy();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
            playVideoSize();
            Log.e("chris_magic", "00000");
        } else {
            playVideoSize();
            Log.e("chris_magic", "1111");
        }
    }

    private void playVideoSize() {
        if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
            int smallH = screen_width * screen_width / screen_height;
            layout.setLayoutParams(new RelativeLayout.LayoutParams(screen_width, smallH));
        } else {
            layout.setLayoutParams(new RelativeLayout.LayoutParams(screen_height, screen_width));
        }
    }

    class GlBufferView extends GLSurfaceView {
    	private MyRenderer mRenderer;
        @Override
		public void onPause() {
			// TODO Auto-generated method stub
			super.onPause();
		}

		public GlBufferView(Context context, AttributeSet attrs) {
            super(context, attrs);
//            (new Thread() {
//                @Override
//                public void run() {
//                    while (true) {
//                        Log.e("chris", "media_handle = " + media_handle);
//                        if (media_handle != 0) {
//                            Log.e("chris", "media_handle = " + media_handle);
//                            break;
//                        }
//                    }
//                   // xPlayer.openglInit();
//                    Log.e("chris", "opengl Init end");
//                }
//            }).start();
            mRenderer = new MyRenderer();
            setRenderer(mRenderer);
            requestFocus();
            setFocusableInTouchMode(true);
        }

        class MyRenderer implements GLSurfaceView.Renderer {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig c) { /* do nothing */
            }

            @Override
            public void onSurfaceChanged(GL10 gl, int w, int h) {
                xPlayer.openglResize(w, h, display_width, display_height);
            }

            @Override
            public void onDrawFrame(GL10 gl) { // update???
                xPlayer.openglRend();
            }
        }
    }

    // *****************api interface	**********/
    public int yyPlayerInit(String url) {
        xPlayer = new XPlayer();
        //register callback function			/add 20130718
        TestCallBack testCallBk = new TestCallBack();
        xPlayer.initCall(testCallBk);
        
        media_handle = xPlayer.initVideo(url);
        Log.e("chris_magic", "after initVideo function ");
        return media_handle;
    }

    public void yyPlayerPlay(int display_w, int display_h) {
        display_width = display_w;
        display_height = display_h;
        xPlayer.xplayerPlay(media_handle);
        Log.e("chris_magic", "before new glBufferview ");
        glBufferView = new GlBufferView(MainActivity.this, null);
    }

    public void yyPlayerStop(int handle) {
        xPlayer.xplayerStop(handle);
    }

    private static float app_density = 0.1f;

    private static int screen_width;

    private static int screen_height;

    public static void initDip2px(Context context) {
        if (null != context) {
            DisplayMetrics metrics = context.getResources().getDisplayMetrics();
            app_density = metrics.density;
            screen_width = metrics.widthPixels;
            screen_height = metrics.heightPixels;
        }
    }
    
    
    public class TestCallBack implements CallBackFun{

		@Override
		public void onPrepare() {
			// TODO Auto-generated method stub
			Log.e("CB", "..in onPrepare function");
		}

		@Override
		public void onError(int errorCode) {
			// TODO Auto-generated method stub
			Log.e("CB", "in onError function ,errorCode = " + errorCode);
		}
    	
    }
}
