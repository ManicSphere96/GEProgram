#pragma once

#pragma warning(disable: 26812) // emum type warning 

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>

#include "Entity.h"
#include "Component.h"
#include "Screen.h"
//#include <myengine/SphereCollider.h>
#include "Environment.h"
#include "Keyboard.h"
#include "Transform.h"
#include "TriangleRenderer.h"
#include "Trigger.h"
#include "Model.h"
#include "Mouse.h"
//#include "Sound.h"
#include "Resource.h"
#include "MeshRenderer.h"


namespace myengine
{

	struct Core
	{
	public:
		static std::shared_ptr<Core> initialize();
		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Environment> getEnvironment();
		std::shared_ptr<Keyboard> getKeyboard();
		//void registerCollider(std::shared_ptr<SphereCollider> collider);
		//void unregisterCollider(std::shared_ptr <SphereCollider> collider);
		void start();
		void stop();
	private:
		bool m_Running;
		std::vector<std::shared_ptr<Entity> > m_Entities;
		std::vector<std::shared_ptr<SphereCollider> > m_CollidersVect;
		std::vector<std::shared_ptr<Resource> > m_Recources;
		std::shared_ptr<Environment> m_Environment;
		std::shared_ptr<Screen> m_Screen;
		std::shared_ptr<Keyboard> m_Keyboard;
		//std::shared_ptr<Sound> sound;
		std::weak_ptr<Core> m_CoreSelf;
		SDL_Window* m_Window;
		ALCdevice* m_Device;
		ALCcontext* m_Context;
	};
}