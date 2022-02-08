#pragma once

#include <string>

namespace myengine
{
	
	struct Resource 
	{
		public:
			std::string m_Path;
			std::string m_VertPath;
			std::string m_FragPath;
			virtual void onInit();
	};
}