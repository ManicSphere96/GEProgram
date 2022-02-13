#pragma once

#pragma warning(disable: 26812) // emum type warning
#include <SDL2/SDL.h>

namespace myengine
{
	struct Screen
	{
		public:
			void setWidth(int w);
			void setHeight(int h);
			int getWidth();
			int getHeight();
		private:
			int m_Width;
			int m_Height;
	};
}