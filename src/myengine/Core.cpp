#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Core.h"

namespace myengine
{
	std::shared_ptr<Core> Core::initialize()
	{
		/**
		 * \brief Sets up the entire program
		 * by intializing everything which is required
		 * to run the program
		 */

		// Creates a shared pointer which will be assinged to core
		std::shared_ptr<Core> corePtr = std::make_shared<Core>();

		// It will then return the shared ptr to a weak pointer 
		//which is assigned to core 
		corePtr->self = corePtr;

		// brief Creates a shared pointer which will be assinged to screen.
		// This will allow the shared pointer to acess functions from the
		// screen header file
		corePtr->screen = std::make_shared<Screen>();
		corePtr->keyboard = std::make_shared<Keyboard>();
		corePtr->environment = std::make_shared<Environment>();
		corePtr->sound = std::make_shared<Sound>();

		corePtr->screen->setWidth(800);
		corePtr->screen->setHeight(800);

		// This will check to see if the SDL video library has been initialized
		// If it hasn't been initialized it will then throw an exception
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::exception();
		}

		// Creates an SDL window and also get the width and height of the screen
		corePtr->window = SDL_CreateWindow("My Engine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			corePtr->screen->getWidth(), corePtr->screen->getHeight(), 
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		// Checks to see if an OpenGL context has been created for the window
		// If it hasn't been created it will then throw an exception
		if (!SDL_GL_CreateContext(corePtr->window))
		{
			throw std::exception();
		}

		// Checks to see if glew has been initialized 
		// If it hasn't been initialized it will then throw an exception
		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		corePtr->device = alcOpenDevice(NULL);

		if (!corePtr->device)
		{
			throw std::exception("Failed to open audio device");
		}

		corePtr->context = alcCreateContext(corePtr->device, NULL);

		if (!corePtr->context)
		{
			alcCloseDevice(corePtr->device);
			throw std::exception("Failed to make audio current");
		}

		if (!alcMakeContextCurrent(corePtr->context))
		{
			alcDestroyContext(corePtr->context);
			alcCloseDevice(corePtr->device);
			throw std::exception("Failed to make context current");
		}

		glClearColor(0, 0, 1, 1);

		// Sets the running bool variable to true
		corePtr->running = true;

		// It will then return the shared pointer
		return corePtr;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		/**
		 * \brief Creates an entity which is then added
		 * to a vector which is used to store all of the entities
		 */

		// Creates a shared pointer which will be assinged to entity
		std::shared_ptr<Entity> entityPtr = std::make_shared<Entity>();

		// This shared pointer is then assigned to a weak pointer
		// and the reassigned to itself
		entityPtr->core = self;
		entityPtr->self = entityPtr;
		entityPtr->transform = entityPtr->addComponent<Transform>();

		// The shared pointer is then added to the entities vector
		entities.push_back(entityPtr);

		// It will then return the shared pointer
		return entityPtr;
	}


	std::shared_ptr<Environment> Core::getEnvironment()
	{
		/// Returns the environment from the core

		return environment;
	}

	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		/// Returns the keyboard from the core

		return keyboard;
	}


	void Core::registerCollider(std::shared_ptr<SphereCollider> collider)
	{
		collidersVect.push_back(collider);
	}

	void Core::unregisterCollider(std::shared_ptr <SphereCollider> collider)
	{
		for (int i = 0; i < collidersVect.size(); i++)
		{
			if (collidersVect[i] == collider)
			{
				collidersVect.erase(collidersVect.begin() + i);
			}
		}
	}

	void Core::start()
	{
		/**
		 * \brief Runs the main game loop.
		 * From there it will then run tick and display functions
		 * to show all of the entities created
		 */

		/// Sets a bool value to true so the game loop can run

		// It will first check to see if the running bool 
		// variable is true
		while (running)
		{
			SDL_Event incomingEvent;

			while (SDL_PollEvent(&incomingEvent))
			{
				if (incomingEvent.type == SDL_QUIT)
				{
					stop();
				}
				else if (incomingEvent.type == SDL_KEYDOWN)
				{
					keyboard->keys.push_back(incomingEvent.key.keysym.sym);
				}
				else if (incomingEvent.type == SDL_KEYUP)
				{
					keyboard->removeKey(incomingEvent.key.keysym.sym);
				}
			}

			environment->tick();

			glEnable(GL_CULL_FACE);

			glEnable(GL_DEPTH_TEST);

			// It will then run a for loop checking each entity in the
			// entities vector and then run the tick function 
			for (size_t ei = 0; ei < entities.size(); ++ei)
			{
				entities.at(ei)->tick();
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			for (size_t ei = 0; ei < entities.size(); ++ei)
			{
				entities.at(ei)->display();
			}


			glDisable(GL_CULL_FACE);

			glDisable(GL_DEPTH_TEST);

			SDL_GL_SwapWindow(window);
		}
	}

	void Core::stop()
	{
		running = false;
	}
}