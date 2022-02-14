#include "Keyboard.h"
#include <iostream>
namespace myengine
{
	bool Keyboard::isKeyDown(int keyCode)
	{
		/// Runs a for loop to see if a key has been pressed. If it has it will return true
		for (int i = 0; i < (int)m_Keys.size(); i++)
		{
			if (m_Keys.at(i) == keyCode)
			{
				std::cout << keyCode;
				return true;
			}
		}
		return false;
	}

	bool Keyboard::isKeyUp(int keyCode)
	{
		///brief Checks to see if a key which has previously been pressed is 
		///now not being pressed
		return false;
	}

	void Keyboard::removeKey(SDL_Keycode key)
	{
		
		///brief Runs a for loop and will remove any keys which are not being pressed
		

		for (int i = 0; i < (int)m_Keys.size(); i++)
		{
			if (m_Keys.at(i) == key)
			{
				m_Keys.erase(m_Keys.begin() + i);
				i--;
			}
		}
	}
}