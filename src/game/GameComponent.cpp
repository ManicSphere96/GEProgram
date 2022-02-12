#include "GameComponent.h"

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

}
void GameComponent::testForCollision()
{
	if (this->getEntity()->getComponent <SphereCollider>()->getHasCollided())
	{
		//this->getEntity()->getComponent<SoundSource>()->playClip();
		this->getEntity()->getComponent <SphereCollider>()->toggleHasCollided();
	}
}