#include "GameComponent.h"

void GameComponent::testForDestroy()
{
	
	if ((!this->getTransform()->getIsPlayer()) && (!this->getTransform()->getMovable()))
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
	testForDestroy();
	testForWin();
}
void GameComponent::testForWin()
{

}