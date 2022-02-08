#pragma once


#include <iostream>
#include <string>
#include "Component.h"
namespace myengine
{

	struct Model : Component
	{
		public:
			Model();
			void onInit(std::string path);
			 
		private:
			std::string m_Path;
	};
}