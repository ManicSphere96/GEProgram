#pragma once

#include <string>

namespace myengine
{
	
	struct Resource
	{
		public:
			Resource( std::string thepath);
			Resource();
			void onInit(std::string thepath);
		private:
			
			
			std::string m_Path;

	};
}