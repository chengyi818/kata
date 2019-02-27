LOCAL_PATH:= $(call my-dir)

# 清除除了LOCAL_PATH外的所有变量
include $(CLEAR_VARS)

# 定义项目的java代码目录
src_dirs := app/src/main/java

# 定义项目的res目录
res_dirs := app/src/main/res

# support包的根目录，因为编译时我们只能引用来自于framework的support包
support_library_root_dir := frameworks/support

# 设置java源码，我们也可以单独指定一个java文件，多个文件需要用空格隔开
LOCAL_SRC_FILES := $(call all-java-files-under, $(src_dirs))

# 设置Res目录，多个目录，可以用空格隔开
LOCAL_RESOURCE_DIR := $(addprefix $(LOCAL_PATH)/, $(res_dirs)) \
    $(support_library_root_dir)/v7/appcompat/res

# 指定Manifest文件
LOCAL_MANIFEST_FILE := app/src/main/AndroidManifest.xml

# aapt，重复资源自动覆盖，每个包含res的依赖库，都必须在这里添加
LOCAL_AAPT_FLAGS += \
    --auto-add-overlay \
    --extra-packages android.support.v7.appcompat \

# 依赖库，java静态库
LOCAL_STATIC_JAVA_LIBRARIES := \
    android-support-v7-appcompat \
    android-support-v4

# 禁用java混淆
LOCAL_PROGUARD_ENABLED := disabled

# 禁用DEX预先优化
LOCAL_DEX_PREOPT := false

# 编译出来的APK名称
LOCAL_PACKAGE_NAME := IACTest3

# 使用平台签名，如果安装在当前源码编译出的ROM中，默认成为系统应用。
LOCAL_CERTIFICATE := platform

# BUILD_PACKAGE 是一个预定义的宏，里面包含编译一个APK的脚本。
include $(BUILD_PACKAGE)
