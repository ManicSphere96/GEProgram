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
			/// the screen width
			int m_Width;
			/// the screen height 
			int m_Height;
	};
}