#include "GameComponent.h"
#include <chrono>
#include <thread>
void GameComponent::testForDestroy()
{
	if (this->getEntity()->getComponent <SphereCollider>() != NULL)
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
		m_Win = true;
		getCore()->getEntityByName("endscreen")->getComponent<SoundSource>()->playClip();
		getCore()->getEntityByName("endscreen")->getComponent<MeshRenderer>()->setVisible(true);
	}
	if (m_Win && (addDeltaTime() > 3.0f))
	{
		getCore()->stop();
	}

}
void GameComponent::testForCollision()
{
	if (this->getEntity()->getComponent <SphereCollider>() != NULL)
	{
		if (this->getEntity()->getComponent <SphereCollider>()->getHasCollided())
		{
			this->getEntity()->getComponent<SoundSource>()->playClip();
			this->getEntity()->getComponent <SphereCollider>()->toggleHasCollided();
		}
	}
}
float GameComponent::addDeltaTime()
{
	m_AddDeltaTime += getCore()->getEnvironment()->getDeltaTime();
	return (m_AddDeltaTime);
}

