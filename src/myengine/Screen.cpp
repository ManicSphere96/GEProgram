#include "Screen.h"

namespace myengine
{
	void Screen::setWidth(int w)
	{
		/// Sets the width for the screen using the parameter provided

		width = w;
	}

	void Screen::setHeight(int h)
	{
		/// Sets the height for the screen using the parameter provided

		height = h;
	}

	int Screen::getWidth()
	{
		/// Returns the width of the screen

		return width;
	}

	int Screen::getHeight()
	{
		/// Returns the height of the screen

		return height;
	}
}