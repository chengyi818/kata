LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    main.cc \

LOCAL_SHARED_LIBRARIES := \

LOCAL_STATIC_LIBRARIES := \

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/ \
    bionic \

ifeq ($(shell expr $(PLATFORM_SDK_VERSION) "<" 23), 1)
    LOCAL_SHARED_LIBRARIES += libstlport
    LOCAL_C_INCLUDES += \
        bionic/libstdc++/include \
        external/stlport/stlport
endif

LOCAL_C_INCLUDES += \

LOCAL_CFLAGS += -pie -fPIE

LOCAL_MODULE:= dlopen_test

LOCAL_MULTILIB := both
LOCAL_MODULE_STEM_32 := $(LOCAL_MODULE)_32
LOCAL_MODULE_STEM_64 := $(LOCAL_MODULE)_64

include $(BUILD_EXECUTABLE)
