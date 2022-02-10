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
#include <SphereCollider.h>
#include "Environment.h"
#include "Keyboard.h"
#include "Transform.h"
#include "TriangleRenderer.h"
#include "Trigger.h"
#include "Model.h"
#include "Mouse.h"
//#include "Sound.h"
#include "Resource.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "TextureResource.h"


namespace myengine
{

	struct Core
	{
	public:
		static std::shared_ptr<Core> initialize();
		void FlushCore();
		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Environment> getEnvironment();
		std::shared_ptr<Keyboard> getKeyboard();
		std::shared_ptr<Resources> getResources() { return m_Resources; }
		void registerCollider(std::shared_ptr<SphereCollider> collider);
		void unregisterCollider(std::shared_ptr <SphereCollider> collider);
		void start();
		void stop();
		void RemoveEntity(std::shared_ptr<Entity> delteentity);
	private:
		bool m_Running;
		std::vector<std::shared_ptr<Entity> > m_Entities;
		std::vector<std::shared_ptr<SphereCollider> > m_CollidersVect;
		std::shared_ptr<Resources> m_Resources;
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