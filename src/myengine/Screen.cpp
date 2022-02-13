#include "Screen.h"

namespace myengine
{
	void Screen::setWidth(int w)
	{
		/// Sets the width for the screen using the parameter provided

		m_Width = w;
	}

	void Screen::setHeight(int h)
	{
		/// Sets the height for the screen using the parameter provided

		m_Height = h;
	}

	int Screen::getWidth()
	{
		/// Returns the width of the screen

		return m_Width;
	}

	int Screen::getHeight()
	{
		/// Returns the height of the screen

		return m_Height;
	}
}