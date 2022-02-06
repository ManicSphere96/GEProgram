#pragma once

#pragma warning(disable: 26812) // emum type warning
#include <SDL2/SDL.h>

namespace myengine
{
	struct Environment
	{
		public:
			Environment();
			float getDeltaTime();
			void tick();
		private:
			float dt;
			float last;
	};
}