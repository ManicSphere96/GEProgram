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
		///Returns the resource list
		std::shared_ptr<Resources> getResources() { return m_Resources; }
		///returns the entities list
		std::vector<std::shared_ptr<Entity> >getEntities() { return m_Entities; }
		void registerCollider(std::shared_ptr<myengine::SphereCollider> collider);
		void unregisterCollider(SphereCollider* collider);
		void registerConvexCollider(std::shared_ptr<myengine::ConvexCollider> convexCollider);
		void unregisterConvexCollider(ConvexCollider* convexCollider);
		void start();
		void stop();
		void removeEntity(std::shared_ptr<Entity> delteentity);
		std::shared_ptr<Entity> getEntityByName(std::string name);
		///returns the path
		std::string getPath(){return m_Path;}
	
	
	private:
		///Holds the Bool saying if the game is running
		bool m_Running = false;
		///Holds the path to the core
		std::string m_Path;
		///Holds the list of donvex colliders
		std::vector<std::shared_ptr<ConvexCollider> > m_ConvexCollidersVect;
		///Holds the  list of all entities
		std::vector<std::shared_ptr<Entity> > m_Entities;
		///Holds the list of all sphere colliders
		std::vector<std::shared_ptr<SphereCollider> > m_CollidersVect;
		///Holds the list of all resources
		std::shared_ptr<Resources> m_Resources;
		///Holds the environment
		std::shared_ptr<Environment> m_Environment;
		///Holds the screen
		std::shared_ptr<Screen> m_Screen;
		///Holds the  keyboard
		std::shared_ptr<Keyboard> m_Keyboard;
		///Holds itself
		std::weak_ptr<Core> m_CoreSelf;
		///Holds the window
		SDL_Window* m_Window = NULL;
		///Holds the sound device
		ALCdevice* m_Device = NULL;
		///Holds the sound context
		ALCcontext* m_Context = NULL;
	};
}