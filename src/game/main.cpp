#include <iostream>
#include <fstream>
#include <core.h>


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
   std::cout << "Hello World!" << std::endl;

   std::shared_ptr<Core> core = Core::initialize();

   //std::shared_ptr<Entity> boxEntityPtr = core->addEntity();
   //std::shared_ptr<Entity> ModelRend = core->addEntity();
   //boxEntityPtr->addComponent<Model, std::string>("Debug\\curuthers");
  // boxEntityPtr->addComponent<Test111>();
   
   //std::shared_ptr<Entity> entity = core->addEntity();
   
   
   std::ifstream levelFile;
   levelFile.open("Debug\\Assets\\LevelFiles\\Level1.txt");

   float x, y, z, scale, rotationX, rotationY, rotationZ, frictionConstant, colliderSize;
   std::string model, vert, frag, texture;
   bool isPlayer, isGravity, isMoveable;




   int entityNumber;
   levelFile >> entityNumber;
   for (int ei = 0; ei < entityNumber; ei++)
   {
	   levelFile >> x >> y >> z >> scale >> rotationX >> rotationY >> rotationZ >> frictionConstant >> colliderSize >> model >> vert >> frag >> texture >> isPlayer >> isGravity >> isMoveable;
	   std::shared_ptr<Entity> entity = core->addEntity();
	   std::shared_ptr<MeshRenderer> mr = entity->addComponent<MeshRenderer>();
	   entity->getTransform()->setPosition(glm::vec3(x, y, z));
	   entity->getTransform()->setScale(glm::vec3(scale, scale, scale));
	   entity->getTransform()->rotate(glm::vec3(rotationX, rotationY, rotationZ));
	   entity->getTransform()->SetIsPlayer(isPlayer);
	   entity->getTransform()->setFriction(frictionConstant);
	   mr->setMesh(core->getResources()->load<Mesh>(model));
	   mr->setShader(core->getResources()->load<Shader>(vert, frag));
	   mr->setTexture(core->getResources()->load<TextureResource>(texture));
	   if (!isGravity)
	   {
		   entity->getTransform()->gravityToggle();
	   }
	   if (!isMoveable)
	   {
		   entity->getTransform()->movableToggle();
	   }
	   if (colliderSize != 0.0)
	   {
		   std::shared_ptr<SphereCollider> col1 = entity->addComponent<SphereCollider>(colliderSize);
	   }
   }
   core->start();

   return 0;
}