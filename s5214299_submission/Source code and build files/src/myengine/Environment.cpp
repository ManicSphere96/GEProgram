#pragma warning(disable: 26812) // emum type warning
#include <iostream>

#include "Environment.h"

typedef std::chrono::high_resolution_clock Clock;

namespace myengine
{
	Environment::Environment()
	{
		///Initializes delta time per frame
		m_Dt = 0.033f;
		m_Last = Clock::now();
	}

	float Environment::getDeltaTime()
	{
		/// Returns delta time

		return (m_Dt > 0.033f) ? 0.033f: m_Dt;
	}

	void Environment::tick()
	{
		/// Calculates current delta time
		std::chrono::time_point<std::chrono::high_resolution_clock> current = Clock::now();
		std::chrono::duration<double> diff = current - m_Last;

		m_Dt = (float)diff.count();
		std::cout << "dt:" << m_Dt << std::endl;
		m_Last = current;
	}
}