#include "Configuration.hpp"

using namespace Asteroids;

Configuration::Configuration(android_app* app): _app(app), _rotation(ROTATION_0)
{
	JavaVM* vm = _app->activity->vm;
        JavaVMAttachArgs args;
	args.version = JNI_VERSION_1_6;
	args.name = "NativeThread";
	args.group = NULL;

        JNIEnv* env;
        vm->AttachCurrentThread(&env, &args);
	findRotation(env);
	_app->activity->vm->DetachCurrentThread();
}

void Configuration::findRotation(JNIEnv* env) 
{
        jobject activity = _app->activity->clazz;

	//Classes
	jclass activityClass = env->GetObjectClass(activity);
	jclass contextClass = env->FindClass("android/content/Context");
	jclass windowManagerClass = env->FindClass("android/view/WindowManager");
	jclass displayClass = env->FindClass("android/view/Display");

	//Methods
	jmethodID getSystemServiceMethod = env->GetMethodID(activityClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
        jmethodID getDefaultDisplayMethod = env->GetMethodID(windowManagerClass, "getDefaultDisplay", "()Landroid/view/Display;");
        jmethodID getRotationMethod = env->GetMethodID(displayClass, "getRotation", "()I");

	jfieldID windowServiceField = env->GetStaticFieldID(contextClass, "WINDOW_SERVICE", "Ljava/lang/String;");

	jobject windowService = env->GetStaticObjectField(contextClass, windowServiceField);
	jobject windowManager = env->CallObjectMethod(activity, getSystemServiceMethod, windowService);
	jobject display = env->CallObjectMethod(windowManager, getDefaultDisplayMethod);

	_rotation = static_cast<Rotation>(env->CallIntMethod(display, getRotationMethod));

        env->DeleteLocalRef(activityClass);
        env->DeleteLocalRef(contextClass);
        env->DeleteLocalRef(windowManagerClass);
        env->DeleteLocalRef(displayClass);
}

Configuration::Rotation Configuration::rotation() const
{
	return _rotation;
}

