#include <iostream>
#include <fstream>
#include <core.h>
#include "GameComponent.h"


using namespace myengine;

struct EngineStopper : Component
{
	virtual void onTick()
	{
		std::cout << "Stopping!" << std::endl;
		getCore()->stop();
	}
};

int main()
{
	std::vector<std::string> LevelList = { "Level1.txt", "Level2.txt" };


	std::cout << "Hello World!" << std::endl;

	std::shared_ptr<Core> core = Core::initialize();

	std::ifstream levelFile;
	for(int i = 0; i < LevelList.size(); i++)
	{
		levelFile.open("Debug\\Assets\\LevelFiles\\" + LevelList[0]);

		float x, y, z, scale, rotationX, rotationY, rotationZ, frictionConstant, colliderSize;
		std::string entityName, model, vert, frag, texture, objSound;
		bool isPlayer, isGravity, isMoveable, isVisible, canDie;




		int entityNumber;
		levelFile >> entityNumber;
		for (int ei = 0; ei < entityNumber; ei++)
		{
			levelFile >> entityName >> x >> y >> z >> scale >> rotationX >> rotationY >> rotationZ >> frictionConstant >> colliderSize >> model >> vert >> frag >> texture >> objSound >> isPlayer >> isGravity >> isMoveable >> isVisible >> canDie;
			std::shared_ptr<Entity> entity = core->addEntity();
			std::shared_ptr<MeshRenderer> mr = entity->addComponent<MeshRenderer>();
			std::shared_ptr<GameComponent> gc = entity->addComponent<GameComponent>();
			entity->getTransform()->setPosition(glm::vec3(x, y, z));
			entity->getTransform()->setScale(glm::vec3(scale, scale, scale));
			entity->getTransform()->rotate(glm::vec3(rotationX, rotationY, rotationZ));
			entity->getTransform()->setIsPlayer(isPlayer);
			entity->getTransform()->setFriction(frictionConstant);
			mr->setMesh(core->getResources()->load<Mesh>(model));
			mr->setShader(core->getResources()->load<Shader>(vert, frag));
			mr->setTexture(core->getResources()->load<TextureResource>(texture));
			entity->setName(entityName);
			mr->setVisible(isVisible);
			
			if (!isGravity)
			{
				entity->getTransform()->gravityToggle();
			}
			if (!isMoveable)
			{
				entity->getTransform()->movableToggle();
			}
			if (colliderSize > 0.0)
			{
				std::shared_ptr<SphereCollider> col1 = entity->addComponent<SphereCollider>(colliderSize);
				if (!canDie)
				{
					entity->getComponent<SphereCollider>()->toggleCanDie();
				}
			}
			if (colliderSize < 0.0)
			{
				std::shared_ptr<ConvexCollider> col1 = entity->addComponent<ConvexCollider>(mr->getMesh()->getVao());
			}
			
			std::shared_ptr<Sound> sound = core->getResources()->load<Sound>(objSound);
			std::shared_ptr<SoundSource> source = entity->addComponent<SoundSource>();
			source->setClip(sound);

		}

		levelFile.close();
		core->start();
		core->flushCore();

	}
   return 0;
}