#pragma once
#include <memory>
#include <vector>
#include <string>
namespace myengine
{
	struct Component;
	struct Core;
	struct Transform;
	struct SphereCollider;

	struct Entity
	{
		public:
			

			template <typename T>
			std::shared_ptr<T> addComponent()
			{
				/// Adds a component to an entity

				// Creates a shared pointer for the component
				std::shared_ptr<T> componentPtr = std::make_shared<T>();

				// It will then assign the shared pointer to a weak pointer
				componentPtr->m_Entity = m_EntitySelf;

				// Adds the shared pointer to the component vector
				m_Components.push_back(componentPtr);
				componentPtr->onInit();

				// It then returns the shared pointer 
				return componentPtr;
			}

			template <typename T, typename A>
			std::shared_ptr<T> addComponent(A a)
			{
				/// Adds a component to an entity and assigns a parameter to it

				
				std::shared_ptr<T> componentPtr = std::make_shared<T>();
				componentPtr->m_Entity = m_EntitySelf;
				m_Components.push_back(componentPtr);
				componentPtr->onInit(a);
				return componentPtr;
			}

			template <typename T, typename A, typename B>
			std::shared_ptr<T> addComponent(A a, B b)
			{
				/// Adds a component to an entity and assigns two parameter to it
				std::shared_ptr<T> componentPtr = std::make_shared<T>();
				componentPtr->m_Entity = m_EntitySelf;
				m_Components.push_back(componentPtr);
				componentPtr->onInit(a,b);
				return componentPtr;
			}

			template <typename T, typename A, typename B, typename C>
			std::shared_ptr<T> addComponent(A a, B b, C c)
			{
				/// Adds a component to an entity and assigns three parameter to it
				std::shared_ptr<T> componentPtr = std::make_shared<T>();
				componentPtr->m_Entity = m_EntitySelf;
				m_Components.push_back(componentPtr);
				componentPtr->onInit(a,b,c);
				return componentPtr;
			}

			template <typename T>
			std::shared_ptr<T> getComponent()
			{
				/// Returns the component 
				for (size_t ci = 0; ci < m_Components.size(); ci++)
				{
					std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(m_Components.at(ci));

					if (rtn)
					{
						return rtn;
					}
				}
				return std::shared_ptr<T>(NULL);
			}


			std::shared_ptr<Core> getCore();
			std::shared_ptr<Transform> getTransform();
			///Sets the name of the entity
			void setName(std::string name) { m_MyName = name; }
			///Returns the name of the entity
			std::string getName() {return m_MyName; }
			void toggleDeletion();
			~Entity();
		private:
			friend struct myengine::Core;
			///Holds a list of all the components
			std::vector<std::shared_ptr<Component>> m_Components;
			///Holds the core
			std::weak_ptr<Core> m_Core;
			///Holds the transform for this entity
			std::weak_ptr<Transform> m_Transform;
			///Holds itself
			std::weak_ptr<Entity> m_EntitySelf;
			///Holds the name of the entity
			std::string m_MyName;
			void tick();
			void display();
			///Holds the boolean deciding to destroy the entity
			bool m_DestroyMe = false;
	};
}