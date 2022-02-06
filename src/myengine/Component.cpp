#include "Component.h"
#include "Entity.h"
#include "Core.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Transform.h"


namespace myengine
{
	std::shared_ptr<Core> Component::getCore()
	{
		/// Returns the core
		return getEntity()->getCore();
	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		/// Returns the entity
		return m_Entity.lock();
	}

	std::shared_ptr<Environment> Component::getEnvironment()
	{
		/// Returns the environment
		return getCore()->getEnvironment();
	}

	std::shared_ptr<Keyboard> Component::getKeyboard()
	{
		/// Returns the keyboard
		return getCore()->getKeyboard();
	}

	std::shared_ptr<Transform> Component::getTransform()
	{
		/// Returns the transform
		return getEntity()->getTransform();
	}


	void Component::tick()
	{
		// Runs the onTick function
		onTick();
	}

	void Component::display()
	{
		// Runs the onTick function
		onDisplay();
	}

	void Component::play()
	{
		// Runs the onTick function
		onPlay();
	}

	void Component::onTick()
	{
		/// Runs the virtual function onTick

		/**
		* The function will run every frame 
		* while the program is running
		*/
	}

	void Component::onDisplay()
	{
		/// Runs the virtual function onDisplay

		/**
		* The function will display a model/triangle.
		* This will depend on which component has been used 
		* (model/triangle renderer)
		*/
	}

	void Component::onPlay()
	{

	}

	void Component::onInit()
	{
		/// Runs the virtual function onInit

		/**
		* The function will initialize all the values used
		* to display a model/triangle
		*/
	}
}