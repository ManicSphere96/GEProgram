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
			/// The path for this rescource

			std::string m_Path;
	};
}