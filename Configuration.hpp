#ifndef ASTEROIDS_CONFIGURATION_HPP
#define ASTEROIDS_CONFIGURATION_HPP

#include <android_native_app_glue.h>
#include <jni.h>

namespace Asteroids
{
    //Using this to find screen rotation (need for G-Sensor)
    class Configuration {
    public:
        Configuration(android_app* app);

	enum Rotation
	{
	   ROTATION_0 = 0,
	   ROTATION_90 = 1,
	   ROTATION_180 = 2,
           ROTATION_270 = 3
	};

        Rotation rotation() const;

    private:
        void findRotation(JNIEnv* end);

    private:
        android_app* _app;
	Rotation _rotation;

    };
}
#endif
