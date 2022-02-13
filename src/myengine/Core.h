#pragma once

#pragma warning(disable: 26812) // emum type warning 

#define EPSILON 0.5 // clamping small bouncing to this velocity
#define GAMMA 1 // stopping sound on small bounces

#include <memory>
#include <vector>

#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <renderer.h>

#include "Entity.h"
#include "Component.h"
#include "Screen.h"
#include "ConvexCollider.h"
#include "SphereCollider.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Transform.h"
#include "Model.h"
#include "Sound.h"
#include "SoundSource.h"
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
		void flushCore();
		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Environment> getEnvironment();
		std::shared_ptr<Keyboard> getKeyboard();
		std::shared_ptr<Resources> getResources() { return m_Resources; }
		std::vector<std::shared_ptr<Entity> >getEntities() { return m_Entities; }
		void registerCollider(std::shared_ptr<myengine::SphereCollider> collider);
		void unregisterCollider(SphereCollider* collider);
		void registerConvexCollider(std::shared_ptr<myengine::ConvexCollider> convexCollider);
		void unregisterConvexCollider(ConvexCollider* convexCollider);
		void start();
		void stop();
		void removeEntity(std::shared_ptr<Entity> delteentity);
		std::shared_ptr<Entity> getEntityByName(std::string name);
		std::string getPath(){return m_Path;}
	
	
	private:
		bool m_Running = false;
		std::string m_Path;
		std::vector<std::shared_ptr<ConvexCollider> > m_ConvexCollidersVect;
		std::vector<std::shared_ptr<Entity> > m_Entities;
		std::vector<std::shared_ptr<SphereCollider> > m_CollidersVect;
		std::shared_ptr<Resources> m_Resources;
		std::shared_ptr<Environment> m_Environment;
		std::shared_ptr<Screen> m_Screen;
		std::shared_ptr<Keyboard> m_Keyboard;
		std::weak_ptr<Core> m_CoreSelf;
		SDL_Window* m_Window = NULL;
		ALCdevice* m_Device = NULL;
		ALCcontext* m_Context = NULL;
	};
}