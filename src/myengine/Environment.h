#pragma once
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