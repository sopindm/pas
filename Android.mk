LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sasteroids
LOCAL_SRC_FILES := main.cpp EventLoop.cpp Logger.cpp Window.cpp Render.cpp Objects.cpp Types.cpp
LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv1_CM
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)