LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := main.c
LOCAL_ARM_MODE := arm

LOCAL_MODULE := main
LOCAL_CFLAGS += -Os

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_EXECUTABLE)



