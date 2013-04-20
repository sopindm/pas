#include <android/log.h>
#include "Logger.hpp"

using namespace Asteroids;

void Logger::message(const char* message)
{
	__android_log_print(ANDROID_LOG_INFO, "ASTEROIDS", message);
	__android_log_print(ANDROID_LOG_INFO, "ASTEROIDS", "\n");
}
