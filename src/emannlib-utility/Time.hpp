#ifndef __TIME_HPP__
#define __TIME_HPP__

#include <chrono>

namespace goldenduck
{
	class Time
	{
	public:
		static double GetCurrentTime()
		{
			std::chrono::duration<double> t = std::chrono::high_resolution_clock::now().time_since_epoch();
			return t.count();
		}
	};
}

#endif
