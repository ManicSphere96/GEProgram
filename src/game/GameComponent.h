#pragma once
#include <core.h>
#include <string>

using namespace myengine;



struct GameComponent : Component
{
public:
	
	void testForDestroy();
	void testForWin();
	void testForCollision();
	void onTick();
	float addDeltaTime();

private:
	float m_AddDeltaTime = 0.0f;
	bool m_Win = false;

};
