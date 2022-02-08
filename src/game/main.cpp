#include <iostream>
#include <core.h>
#include "Player.h"


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
   
   


   std::shared_ptr<Entity> entity = core->addEntity();
   
   std::shared_ptr<Player> player = entity->addComponent<Player>();
   player->Initialization(glm::vec3(0, 0, -10), 
	   glm::vec3(0.5f, 0.5f, 0.5f), 
	   glm::vec3(0, 0.0f, 0), 
	   "Debug\\Assets\\models\\curuthers\\curuthers",
	   "Debug\\Assets\\Shaders\\vertShader", 
	   "Debug\\Assets\\Shaders\\fragShader", 
	   "Debug\\Assets\\Textures\\Whiskers_diffuse", 
	   true);
   player->SetMoveAmount(0.1f);
	
   
   //std::shared_ptr<MeshRenderer> mr = entity->addComponent<MeshRenderer>();
  /* mr->setMesh(core->getResources()->load<Mesh>("Debug\\Assets\\models\\curuthers\\curuthers"));
   mr->setShader(core->getResources()->load<Shader>("Debug\\Assets\\Shaders\\vertShader", "Debug\\Assets\\Shaders\\fragShader"));
   mr->setTexture(core->getResources()->load<TextureResource>("Debug\\Assets\\Textures\\Whiskers_diffuse"));
   mr->getTransform()->setPosition(glm::vec3(0, 0, -10));
   mr->getTransform()->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
   mr->getTransform()->rotate(glm::vec3(0, 0.0f, 0));*/
   
	
  /* 
   mr->setShader(core->getResources()->load<Shader>("shaders/basic");*/
   
   
   
   

   //std::shared_ptr<Component> component = entity->addComponent<EngineStopper>();
  // std::shared_ptr<TriangleRenderer> triangleRenderer = boxEntityPtr->addComponent<TriangleRenderer>();
   
   //std::shared_ptr<Model> testModel = boxEntityPtr->addComponent<Model>();

   //std::cout << boxEntityPtr->getCore() << std::endl;
   //std::cout << component->getCore() << std::endl;
   //std::cout << component->getEntity() << std::endl;

   core->start();

   return 0;
}