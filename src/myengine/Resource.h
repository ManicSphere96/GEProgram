#pragma once

#include <string>

namespace myengine
{
	
	struct Resource
	{
		public:
			std::string getPath() { return path; }

		private:
			
			virtual void onInit();
			std::string path;

	};
}