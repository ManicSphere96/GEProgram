#pragma once

#include <string>

namespace myengine
{
	
	struct Resource 
	{
		public:
			/// The path for this rescource
			std::string m_Path;
			/// The path for this rescource
			std::string m_VertPath;
			/// The path for this rescource
			std::string m_FragPath;
			virtual void onInit();
	};
}