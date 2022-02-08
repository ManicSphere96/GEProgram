#include "Player.h"

void Player::Initialization(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, std::string meshPath, std::string vertPath, std::string fragPath, std::string texPath, bool isBeingPlayed)
{
	std::shared_ptr<MeshRenderer> mr = getEntity()->addComponent<MeshRenderer>();
	mr->setMesh(getCore()->getResources()->load<Mesh>(meshPath));
	mr->setShader(getCore()->getResources()->load<Shader>(vertPath, fragPath));
	mr->setTexture(getCore()->getResources()->load<TextureResource>(texPath));
	m_IsBeingPlayed = isBeingPlayed;
}



void Player::onTick()
{
	// If the player presses space it will set yMomentum to 1.25
	if (getKeyboard()->isKeyDown(SDLK_UP))
	{
		glm::vec3 currentPos = getTransform()->getPosition();
		currentPos += glm::vec3(0, m_MoveAmount, 0);
		getTransform()->setPosition(currentPos);

	}
	else if (getKeyboard()->isKeyDown(SDLK_DOWN))
	{
		glm::vec3 currentPos = getTransform()->getPosition();
		currentPos += glm::vec3(0, -m_MoveAmount, 0);
		getTransform()->setPosition(currentPos);
	}
	// This will then make the player jump
	else if (getKeyboard()->isKeyDown(SDLK_LEFT))
	{
		glm::vec3 currentPos = getTransform()->getPosition();
		currentPos += glm::vec3(-m_MoveAmount, 0, 0);
		getTransform()->setPosition(currentPos);
	}
	else if (getKeyboard()->isKeyDown(SDLK_RIGHT))
	{
		glm::vec3 currentPos = getTransform()->getPosition();
		currentPos += glm::vec3(m_MoveAmount, 0, 0);
		getTransform()->setPosition(currentPos);
	}

}
void Player::SetMoveAmount(float moveAmount)
{
	m_MoveAmount = moveAmount;
}