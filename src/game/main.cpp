#include <iostream>
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

   std::shared_ptr<Entity> boxEntityPtr = core->addEntity();
   boxEntityPtr->addComponent<Model, std::string>("Debug\\cube2");
   
   //std::shared_ptr<Component> component = entity->addComponent<EngineStopper>();
   std::shared_ptr<TriangleRenderer> triangleRenderer = boxEntityPtr->addComponent<TriangleRenderer>();
   
   //std::shared_ptr<Model> testModel = boxEntityPtr->addComponent<Model>();

   std::cout << boxEntityPtr->getCore() << std::endl;
   //std::cout << component->getCore() << std::endl;
   //std::cout << component->getEntity() << std::endl;

   core->start();

   return 0;
}