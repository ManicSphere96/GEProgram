#pragma once
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
			int width;
			int height;
	};
}