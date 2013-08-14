#ifndef __CUSTOME_JAVA_CB_H
#define __CUSTOME_JAVA_CB_H


#include <jni.h>

//全局变量
JavaVM *g_jvm ;
jobject g_obj;

int call_java_onprepare(jobject obj);


int call_java_onerror(jobject obj ,int codeNo);
#endif
