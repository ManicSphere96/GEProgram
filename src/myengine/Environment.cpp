#pragma warning(disable: 26812) // emum type warning

#include "Environment.h"
#include <SDL2/SDL.h>

namespace myengine
{
	Environment::Environment()
	{
		dt = 0;
		last = (float)SDL_GetTicks();
	}

	float Environment::getDeltaTime()
	{
		/// Returns delta time

		return dt;
	}

	void Environment::tick()
	{
		/// Calculates current delta time

		float current = (float)SDL_GetTicks();
		float diff = current - last;

		dt = diff / 1000.0f;

		last = current;
	}
}