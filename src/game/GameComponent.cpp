#include "GameComponent.h"
#include <chrono>
#include <thread>
void GameComponent::testForDestroy()
{
	
	if ((!this->getTransform()->getIsPlayer()) && (!this->getTransform()->getMovable()) && (this->getComponent<SphereCollider>()->getCanDie() == true))
	{
		if (this->getEntity()->getComponent<SphereCollider>()->getHitCount() > 2)
		{
			this->getEntity()->toggleDeletion();
			this->getEntity()->getComponent<SphereCollider>()->onDestroy();
		}
	}
}
void GameComponent::onTick()
{
	testForCollision();
	testForDestroy();
	testForWin();
}
void GameComponent::testForWin()
{
	if (getCore()->getEntityByName("EndBall")->getComponent<SphereCollider>()->getCollidedName() == "PlayerBall")
	{
		getCore()->getEntityByName("endscreen")->getComponent<MeshRenderer>()->VisibleToggle();
		std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
		getCore()->stop();
	}

}
void GameComponent::testForCollision()
{
	if (this->getEntity()->getComponent <SphereCollider>()->getHasCollided())
	{
		this->getEntity()->getComponent<SoundSource>()->playClip();
		this->getEntity()->getComponent <SphereCollider>()->toggleHasCollided();
	}
}