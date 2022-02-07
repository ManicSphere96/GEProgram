#pragma once
#include <core.h>
#include <string>

using namespace myengine;



struct Test111 : Component
{
public:
	void onInit();


private:
	std::shared_ptr<MeshRenderer> m_MeshRenderer;
	friend struct myengine::MeshRenderer;
	std::shared_ptr<renderer::ShaderProgram> m_ShaderProgram;
};
