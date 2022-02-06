#include "Resource.h"

namespace myengine
{
	Resource::Resource(std::string thepath)
	{
		 m_Path = thepath;
	}
	Resource::Resource()
	{
		m_Path = "";
	}
	void Resource::onInit(std::string thepath)
	{
		m_Path = thepath;
	}
}