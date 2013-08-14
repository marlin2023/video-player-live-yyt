#ifndef LOG_H_
#define LOG_H_

#include <android/log.h>

#define CHRIS 1
#ifdef CHRIS
#define log_chris(priority  ,tag ,...)		__android_log_print(priority  ,tag ,__VA_ARGS__)
//#define log_chris(priority  ,tag ,fmt ,...)		__android_log_print(priority  ,tag ,fmt ,__VA_ARGS__)
#else
#define log_chris(priority, tag,  ...)       ((void)(0))
#endif

#endif
