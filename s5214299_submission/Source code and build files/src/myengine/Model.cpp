#include "Model.h"

namespace myengine
{
	Model::Model()
	{

	}
	void Model::onInit(std::string path)
	{
		///sets the path
		m_Path = path ;
	}
}