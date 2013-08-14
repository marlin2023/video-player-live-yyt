LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
#com_chris_yanlong_XPlayer.c
#com_yinyuetai_tools_live_XPlayer.c
LOCAL_SRC_FILES:=com_chris_yanlong_XPlayer.c	\
				packet_queue.c	\
				decode_audio.c	\
				opensl_audio_play.c	\
				decode_video.c	\
				opengl_video_play.c	\
				picture_queue.c	\
				custom_java_cb.c	\
				xplayer.c				 
				 

LOCAL_C_INCLUDES := $(JNI_H_INCLUDE)

LOCAL_C_INCLUDES += \
/home/chris/work/ffmpeg/refs/ffmpeg-armv7/include

LOCAL_MODULE := libxplayer

LOCAL_SHARED_LIBRARIES := libutils
										
LOCAL_LDLIBS := -fpic  -g  -llog -lz -L/home/chris/work/ffmpeg/refs/ffmpeg-armv7/lib  -lavformat -lavcodec -lswscale -lswresample -lavutil 
LOCAL_LDLIBS += -lOpenSLES 
LOCAL_LDLIBS += -lGLESv1_CM

LOCAL_PRELINK_MODULE := false

LOCAL_PROGUARD_ENABLED := disabled

include $(BUILD_SHARED_LIBRARY)
