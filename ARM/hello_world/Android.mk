LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := hello_world.c
LOCAL_ARM_MODE := arm

LOCAL_MODULE := hello_world

include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_EXECUTABLE)



