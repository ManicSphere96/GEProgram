#pragma once

#pragma warning(disable: 26812) // emum type warning
#include <SDL2/SDL.h>
#include <vector>

namespace myengine
{
	struct Keyboard
	{
		public:
			bool isKeyDown(int keyCode);
			bool isKeyUp(int keyCode);
			void removeKey(SDL_Keycode key);
			// A vector used to store the keys which have been pressed
			std::vector<int> m_Keys;
		private:
			
	};
}