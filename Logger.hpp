#ifndef ASTEROIDS_LOGGER_HPP
#define ASTEROIDS_LOGGER_HPP

namespace Asteroids
{
	class Logger
	{
	public:
		static void message(const char* message);
	};
}

#ifndef NDEBUG
#define ASTEROIDS_LOG(string) Asteroids::Logger::message(string)
#else
#define ASTEROIDS_LOG(string)
#endif

#endif
