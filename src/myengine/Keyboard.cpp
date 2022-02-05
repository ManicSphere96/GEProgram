#include "Keyboard.h"

namespace myengine
{
	bool Keyboard::isKeyDown(int keyCode)
	{
		/**
		 * \brief Runs a for loop to see if a key
		 * has been pressed. If it has it will return 
		 * true, otherwise it will return false
		 */

		for (int i = 0; i < keys.size(); i++)
		{
			if (keys.at(i) == keyCode)
			{
				return true;
			}
		}

		return false;
	}

	bool Keyboard::isKeyUp(int keyCode)
	{
		/**
		 * \brief Checks to see if a key
		 * which has previously been pressed is 
		 * now not being pressed
		 */

		return false;
	}

	void Keyboard::removeKey(SDL_Keycode key)
	{
		/**
		 * \brief Runs a for loop and will remove
		 * any keys which are not being pressed
		 */

		for (int i = 0; i < keys.size(); i++)
		{
			if (keys.at(i) == key)
			{
				keys.erase(keys.begin() + i);
				i--;
			}
		}
	}
}