#include "Entity.h"
#include "Component.h"
#include "Transform.h"

namespace myengine
{
	std::shared_ptr<Core> Entity::getCore()
	{
		/// Returns the core
		return m_Core.lock();
	}

	std::shared_ptr<Transform> Entity::getTransform()
	{
		/// Returns the Transform

		return m_Transform.lock();
	}


	void Entity::tick()
	{
		/// Runs a for loop to check each component which has been added to the entity and then runs the tick function
		
		for (size_t cn = 0; cn < m_Components.size(); cn++)
		{
			m_Components.at(cn)->tick();
		}
	}

	void Entity::display()
	{
		/// Runs a for loop to check each component which has been added to the entity and then runs the display function
		for (size_t ci = 0; ci < m_Components.size(); ci++)
		{
			m_Components.at(ci)->onDisplay();
		}
	}

	Entity::~Entity()
	{
	}

	void Entity::toggleDeletion()
	{ 
		///changes delete from false to true so it can be deleted
		if (!m_DestroyMe)
		{
			m_DestroyMe = true;
		}
	}
}