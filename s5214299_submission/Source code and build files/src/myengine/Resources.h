#pragma once

#include "Resource.h"

#include <vector>
#include <memory>
#include <string>

namespace myengine
{
	struct Resource;

	struct Resources
	{
	public:
		///loading a resource from its pathname
		template <typename T>
		std::shared_ptr<T> load(const std::string& path)
		{
			std::shared_ptr<T> rtn;
			for (size_t resourceIndex = 0; resourceIndex < m_ResourcesVect.size(); resourceIndex++)
			{
				std::shared_ptr<Resource> gvnResource = m_ResourcesVect.at(resourceIndex);
				if (gvnResource->m_Path != path) continue;
				rtn = std::dynamic_pointer_cast<T>(gvnResource);
				if (rtn) return rtn;
			}

			rtn = std::make_shared<T>();
			rtn->m_Path = path;
			rtn->onInit();
			m_ResourcesVect.push_back(rtn);
			return rtn;

		}
		///loading a resource from two pathnames only used for vert and frag shader 
		template <typename T>
		std::shared_ptr<T> load(const std::string& vertpath, const std::string& fragpath)
		{
			std::shared_ptr<T> rtn;
			for (size_t resourceIndex = 0; resourceIndex < m_ResourcesVect.size(); resourceIndex++)
			{
				std::shared_ptr<Resource> gvnResource = m_ResourcesVect.at(resourceIndex);
				if ((gvnResource->m_VertPath != vertpath) && (gvnResource->m_FragPath != fragpath)) continue;
				rtn = std::dynamic_pointer_cast<T>(gvnResource);
				if (rtn) return rtn;
			}

			rtn = std::make_shared<T>();
			rtn->m_VertPath = vertpath;
			rtn->m_FragPath = fragpath;
			rtn->onInit();
			m_ResourcesVect.push_back(rtn);
			return rtn;

		}
		///Assigning a self pointer
		void setSelf(std::shared_ptr<Resources> Ptr) { m_Self = Ptr; }

	private:
		/// Storage for all Resources
		std::vector<std::shared_ptr<Resource>> m_ResourcesVect;
		///Storage for this object
		std::shared_ptr<Resources> m_Self;
	
	};

}