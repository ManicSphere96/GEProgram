#pragma warning(disable: 26812) // emum type warning
#include <iostream>

#include "Environment.h"

typedef std::chrono::high_resolution_clock Clock;

namespace myengine
{
	Environment::Environment()
	{
		dt = 0.033f;
		last = Clock::now();
	}

	float Environment::getDeltaTime()
	{
		/// Returns delta time

		return (dt > 0.033f) ? 0.033f: dt;
	}

	void Environment::tick()
	{
		/// Calculates current delta time
		std::chrono::time_point<std::chrono::high_resolution_clock> current = Clock::now();
		std::chrono::duration<double> diff = current - last;

		dt = (float)diff.count();
		std::cout << "dt:" << dt << std::endl;
		last = current;
	}
}