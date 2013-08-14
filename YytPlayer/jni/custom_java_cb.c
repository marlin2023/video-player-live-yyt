#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include "custom_java_cb.h"

#define TAG "CUSTOM_JAVA_CB_C"
int call_java_onprepare(jobject obj){
	//**** call java function onPrepare , to mean ready ok//
	JNIEnv *env;
	jclass cls;
	jmethodID mid;

	//Attach主线程
	if ((*g_jvm)->AttachCurrentThread(g_jvm, &env, NULL) != JNI_OK) {	//env
		//LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
		return -1;
	}

	cls =  (*env)->GetObjectClass(env, obj);
	if (cls == NULL) {
		__android_log_print(ANDROID_LOG_INFO, TAG ,".......find class is failed");
		return -1;
	}

	mid = (*env)->GetMethodID(env, cls, "onPrepare", "()V"); //public void onPrepare();
	if (mid == NULL) {
		__android_log_print(ANDROID_LOG_INFO, TAG ,".......get method .......id is failed");
		return -1;
	}

	(*env)->CallVoidMethod(env, obj, mid);   //the second parameter value?
	 //Detach主线程
	 if((*g_jvm)->DetachCurrentThread(g_jvm) != JNI_OK)
	 {
		 __android_log_print(ANDROID_LOG_INFO, TAG ,"DetachCurrentThread() failed");
//		 LOGE("%s: DetachCurrentThread() failed", __FUNCTION__);
	 }
	return 0;
}


int call_java_onerror( jobject obj ,int codeNo){
	//**** call java function onError , to mean error happy//
	JNIEnv *env;
	jclass cls;
	jmethodID mid;
	int attached = 0;
//	//Attach主线程
//	if ((*g_jvm)->AttachCurrentThread(g_jvm, &env, NULL) != JNI_OK) {	//env
//		//LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
//		return -1;
//	}

	switch ((*g_jvm)->GetEnv(g_jvm ,(void**)&env, JNI_VERSION_1_6)) //JNI_VERSION_1_6
	  {
	  case JNI_OK:
	    break;
	  case JNI_EDETACHED:
	    if ((*g_jvm)->AttachCurrentThread(g_jvm ,&env, NULL)!=0)
	    {
//	      throw std::runtime_error("Could not attach current thread");
	    }
	    attached = 1;
	    break;
	  case JNI_EVERSION:
		  break;
//	    throw std::runtime_error("Invalid java version");
	  }

	cls =  (*env)->GetObjectClass(env, obj);
	if (cls == NULL) {
		__android_log_print(ANDROID_LOG_INFO, TAG ,".......find class is failed");
		return -1;
	}

	mid = (*env)->GetMethodID(env, cls, "onError", "(I)V");
	if (mid == NULL) {
		__android_log_print(ANDROID_LOG_INFO, TAG ,".......get method  onError.......id is failed");
		return -1;
	}

	(*env)->CallVoidMethod(env, obj, mid ,(jint)codeNo);   //the second parameter value?

	if(attached == 1){
		//	 //Detach主线程
			 if((*g_jvm)->DetachCurrentThread(g_jvm) != JNI_OK)
			 {
				 __android_log_print(ANDROID_LOG_INFO, TAG ,"DetachCurrentThread() failed");
		//		 LOGE("%s: DetachCurrentThread() failed", __FUNCTION__);
			 }
	}

	return codeNo;
}

