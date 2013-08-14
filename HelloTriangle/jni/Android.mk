LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libgljni
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := com_chris_triangle_GLLib.cpp
LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)