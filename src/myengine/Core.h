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


namespace myengine
{

	struct Core
	{
	public:
		static std::shared_ptr<Core> initialize();
		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Environment> getEnvironment();
		std::shared_ptr<Keyboard> getKeyboard();
		void registerCollider(std::shared_ptr<SphereCollider> collider);
		void unregisterCollider(std::shared_ptr <SphereCollider> collider);
		void start();
		void stop();
	private:
		bool running;
		std::vector<std::shared_ptr<Entity> > entities;
		std::vector<std::shared_ptr<SphereCollider> > collidersVect;
		std::vector<std::shared_ptr<Resource> > Recources;
		std::shared_ptr<Environment> environment;
		std::shared_ptr<Screen> screen;
		std::shared_ptr<Keyboard> keyboard;
		//std::shared_ptr<Sound> sound;
		std::weak_ptr<Core> self;
		SDL_Window* window;
		ALCdevice* device;
		ALCcontext* context;
	};
}