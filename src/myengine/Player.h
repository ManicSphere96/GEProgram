#pragma once
#include <string>
#include "Core.h"
#include "component.h"
using namespace myengine;

struct Player : Component
{
public:
	Player() {};
	void Initialization(glm::vec3, glm::vec3, glm::vec3, std::string, std::string, std::string, std::string, bool);
	void onTick();
	void SetMoveAmount(float moveAmount); // could be in onInit??
private:

	float m_MoveAmount;
	bool m_IsBeingPlayed;
};

