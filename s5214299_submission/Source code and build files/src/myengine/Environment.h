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
			///Delta time
			float m_Dt;
			///Holds the last time we took for delta time
			std::chrono::time_point<std::chrono::high_resolution_clock> m_Last;
	};
}