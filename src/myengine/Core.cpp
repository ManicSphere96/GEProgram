#pragma warning(disable: 26812) // emum type warning

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

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
		corePtr->m_CoreSelf = corePtr;

		// brief Creates a shared pointer which will be assinged to screen.
		// This will allow the shared pointer to acess functions from the
		// screen header file
		corePtr->m_Screen = std::make_shared<Screen>();
		corePtr->m_Keyboard = std::make_shared<Keyboard>();
		corePtr->m_Environment = std::make_shared<Environment>();
		std::shared_ptr<Resources> resourcesPtr = std::make_shared<Resources>();
		
		corePtr->m_Resources = resourcesPtr;
		resourcesPtr->setSelf(resourcesPtr);
			//std::make_shared<Resources>();
		
		//corePtr->sound = std::make_shared<Sound>();

		corePtr->m_Screen->setWidth(800);
		corePtr->m_Screen->setHeight(800);

		// This will check to see if the SDL video library has been initialized
		// If it hasn't been initialized it will then throw an exception
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::exception();
		}

		// Creates an SDL window and also get the width and height of the screen
		corePtr->m_Window = SDL_CreateWindow("My Engine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			corePtr->m_Screen->getWidth(), corePtr->m_Screen->getHeight(),
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		// Checks to see if an OpenGL context has been created for the window
		// If it hasn't been created it will then throw an exception
		if (!SDL_GL_CreateContext(corePtr->m_Window))
		{
			throw std::exception();
		}

		// Checks to see if glew has been initialized 
		// If it hasn't been initialized it will then throw an exception
		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		corePtr->m_Device = alcOpenDevice(NULL);

		if (!corePtr->m_Device)
		{
			throw std::exception("Failed to open audio device");
		}

		corePtr->m_Context = alcCreateContext(corePtr->m_Device, NULL);

		if (!corePtr->m_Context)
		{
			alcCloseDevice(corePtr->m_Device);
			throw std::exception("Failed to make audio current");
		}

		if (!alcMakeContextCurrent(corePtr->m_Context))
		{
			alcDestroyContext(corePtr->m_Context);
			alcCloseDevice(corePtr->m_Device);
			throw std::exception("Failed to make context current");
		}

		glClearColor(0, 0, 1, 1);

		// Sets the running bool variable to true
		corePtr->m_Running = true;

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
		entityPtr->m_Core = m_CoreSelf;
		entityPtr->m_EntitySelf = entityPtr;
		entityPtr->m_Transform = entityPtr->addComponent<Transform>();

		// The shared pointer is then added to the entities vector
		m_Entities.push_back(entityPtr);

		// It will then return the shared pointer
		return entityPtr;
	}


	std::shared_ptr<Environment> Core::getEnvironment()
	{
		/// Returns the environment from the core

		return m_Environment;
	}

	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		/// Returns the keyboard from the core

		return m_Keyboard;
	}


	void Core::registerCollider(std::shared_ptr<SphereCollider> collider)
	{
		m_CollidersVect.push_back(collider);
	}

	void Core::unregisterCollider(SphereCollider* collider)
	{

		for (int i = 0; i < (int)m_CollidersVect.size(); i++)
		{
			//std::shared_ptr<SphereCollider> spcolider = collider;
			if (m_CollidersVect[i].get() == collider)
			{
				m_CollidersVect.erase(m_CollidersVect.begin() + i);
				i--;
			}
		}
	}

	void Core::registerConvexCollider(std::shared_ptr<myengine::ConvexCollider> convexCollider)
	{
		m_ConvexCollidersVect.push_back(convexCollider);
	}

	void Core::unregisterConvexCollider(ConvexCollider* convexCollider)
	{

		for (int i = 0; i < (int)m_ConvexCollidersVect.size(); i++)
		{
			//std::shared_ptr<BoxCollider> spcolider = collider;
			if (m_ConvexCollidersVect[i].get() == convexCollider)
			{
				m_ConvexCollidersVect.erase(m_ConvexCollidersVect.begin() + i);
				i--;
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
		m_Running = true;
		while (m_Running)
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
					m_Keyboard->m_Keys.push_back(incomingEvent.key.keysym.sym); 
				}
				else if (incomingEvent.type == SDL_KEYUP)
				{
					m_Keyboard->removeKey(incomingEvent.key.keysym.sym);
				}
			}

			

			glEnable(GL_CULL_FACE);

			glEnable(GL_DEPTH_TEST);

			// Loop through all Sphere colliders check if they are sphere-sphere hits and process.
			for (size_t i = 0; i < m_CollidersVect.size(); i++)
			{
				for (size_t j = i+1; j < m_CollidersVect.size(); j++)
				{
					if (m_CollidersVect[i]->isColliding(m_CollidersVect[j]))
					{
						m_CollidersVect[i]->currentlyColliding( m_CollidersVect[j]);
					}

				}
			}
			// Loop through all Convex colliders check if they are convex-sphere hits and process.
			for (size_t ci = 0; ci < m_ConvexCollidersVect.size(); ci++)
			{
				for (size_t sj = 0; sj < m_CollidersVect.size(); sj++)
				{
					m_ConvexCollidersVect[ci]->isColliding(m_CollidersVect[sj]);
				}
			}
			for (size_t ei = 0; ei < m_Entities.size(); ++ei)
			{
				m_Entities.at(ei)->tick();
			}
			m_Environment->tick();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			for (size_t ei = 0; ei < m_Entities.size(); ++ei)
			{
				if (m_Entities.at(ei)->m_DestroyMe == true)
				{
					removeEntity(m_Entities.at(ei));

					ei--;
				}

			}

			for (size_t ei = 0; ei < m_Entities.size(); ++ei)
			{
				m_Entities.at(ei)->display();
			}


			glDisable(GL_CULL_FACE);

			glDisable(GL_DEPTH_TEST);

			SDL_GL_SwapWindow(m_Window);

			
		}
		
	}

	void Core::stop()
	{
		m_Running = false;
	}
	void Core::flushCore()
	{
		for (size_t ei = 0; ei < m_Entities.size(); ++ei)
		{
			m_Entities.at(ei)->~Entity();
		}

	}
	void Core::removeEntity(std::shared_ptr<Entity> deleteentity)
	{
		for (size_t ei = 0; ei < m_Entities.size(); ++ei)
		{
			if (m_Entities.at(ei) == deleteentity)
			{
				
				
				m_Entities.erase(m_Entities.begin() +ei);
				ei--;
			}
		}

	}
	std::shared_ptr<Entity> Core::getEntityByName(std::string name)
	{
		for (size_t i = 0; i < m_Entities.size(); ++i)
		{
			if (m_Entities.at(i)->getName() == name)
			{
				return m_Entities.at(i);
			}
		}
		throw std::exception("Failed to find entity with this name");
	}
}