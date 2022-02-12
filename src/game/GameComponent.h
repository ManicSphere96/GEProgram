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

private:
	
};
