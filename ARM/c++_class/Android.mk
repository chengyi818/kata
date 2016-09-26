LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := main.cpp
LOCAL_ARM_MODE := arm

#debug
LOCAL_CFLAGS += -O0
#release
#LOCAL_CFLAGS += -O2

LOCAL_MODULE := main
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_EXECUTABLE)



