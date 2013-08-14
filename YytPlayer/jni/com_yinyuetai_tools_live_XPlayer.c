#include "com_yinyuetai_tools_live_XPlayer.h"
#include "log_chris.h"
#include "xplayer.h"
#include "opengl_video_play.h"
#include "custom_java_cb.h"

#define TAG 	"COM_CHRIS_YINEYUETAI_TOOLS_LIVE_XPLAYER"
#ifdef __cplusplus
extern "C" {
#endif


void test(int n,struct siginfo *siginfo,void *myact)
{
//        int i, num;
//        char **calls;
//        printf("Fault address:%X\n",siginfo->si_addr);
//        num = backtrace(buffer, SIZE);
//        calls = backtrace_symbols(buffer, num);
//        for (i = 0; i < num; i++)
//                printf("%s\n", calls[i]);
//        exit(1);
	log_chris(ANDROID_LOG_INFO,TAG, " in signal capture function " );
	call_java_onerror(g_obj ,101);
//	return;
	exit(0);

}
//由java调用来建立JNI环境
void setJNIEnv(JNIEnv* env, jobject obj) {
	//保存全局JVM以便在子线程中使用
	(*env)->GetJavaVM(env, &g_jvm);
	//不能直接赋值(g_obj = obj)
	g_obj = (*env)->NewGlobalRef(env, obj);
}

JNIEXPORT jint JNICALL Java_com_yinyuetai_tools_live_XPlayer_initVideoPlayer
  (JNIEnv * env, jobject obj, jstring media_url){

	//
	 struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=test;
	sigaction(SIGSEGV,&act,NULL);
	//
	setJNIEnv(env ,obj);  //set jni env

	char *input_url = NULL;
	input_url = (char*)(*env)->GetStringUTFChars(env, media_url, NULL);
	log_chris(ANDROID_LOG_INFO,TAG, "open file +%s+ " ,input_url);

	PLAYER_HANDLE media_handle = init_media(input_url );
	(*env)->ReleaseStringUTFChars(env, media_url, input_url);   //release memory allocate by vm

	//
	return (jint)(media_handle);
}


JNIEXPORT jint JNICALL Java_com_yinyuetai_tools_live_XPlayer_play
  (JNIEnv *env, jobject obj ,jint handle){
	xplayer_play((int)handle);
	return 0;

}


JNIEXPORT jint JNICALL Java_com_yinyuetai_tools_live_XPlayer_stopVideoPlayer
  (JNIEnv *env, jobject obj ,jint handle){
	//set file_over = 1
	player_stop((int)handle);
	return 0;
}


JNIEXPORT void JNICALL Java_com_yinyuetai_tools_live_XPlayer_initOpenGL
  (JNIEnv *env, jobject obj){
	opengl_start();
}

JNIEXPORT void JNICALL Java_com_yinyuetai_tools_live_XPlayer_openGLResize
  (JNIEnv *env, jobject obj ,jint screen_w ,jint screen_h ,jint display_w ,jint display_h){
	opengl_resize((int)screen_w ,(int)screen_h ,(int)display_w ,(int)display_h);
}

JNIEXPORT void JNICALL Java_com_yinyuetai_tools_live_XPlayer_openGLRend
  (JNIEnv *env, jobject obj){
	opengl_render();
}

#ifdef __cplusplus
}
#endif
