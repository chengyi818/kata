LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm
LOCAL_MODULE := hello_world
LOCAL_SRC_FILES := hello_world.c

include $(BUILD_SHARED_LIBRARY)
