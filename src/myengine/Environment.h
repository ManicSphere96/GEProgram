#pragma once
#include <chrono>
#pragma warning(disable: 26812) // emum type warning

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
			std::chrono::time_point<std::chrono::high_resolution_clock> last;
	};
}