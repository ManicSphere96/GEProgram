#pragma warning(disable: 26812) // emum type warning

#define WIN32_LEAN_AND_MEAN ///didnt want to add this but had to for windows exe paths
#include <windows.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "Core.h"

namespace myengine
{
	std::shared_ptr<Core> Core::initialize()
	{

		///brief Sets up the entire program by intializing everything which is required
		///to run the program
		

		std::shared_ptr<Core> corePtr = std::make_shared<Core>();
		corePtr->m_CoreSelf = corePtr;

		char  szPath[MAX_PATH];
		
		if (GetModuleFileName(NULL, szPath, sizeof szPath) == 0)
		{
			return std::shared_ptr<Core>(NULL);
		}

		std::string fullPath(szPath);
		corePtr->m_Path = fullPath.substr(0, fullPath.find_last_of("\\/"));



		corePtr->m_Screen = std::make_shared<Screen>();
		corePtr->m_Keyboard = std::make_shared<Keyboard>();
		corePtr->m_Environment = std::make_shared<Environment>();
		std::shared_ptr<Resources> resourcesPtr = std::make_shared<Resources>();
		
		corePtr->m_Resources = resourcesPtr;
		resourcesPtr->setSelf(resourcesPtr);

		corePtr->m_Screen->setWidth(800);
		corePtr->m_Screen->setHeight(800);

		/// This will check to see if the SDL video library has been initialized
		/// If it hasn't been initialized it will then throw an exception
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::exception();
		}

		/// Creates an SDL window and also get the width and height of the screen
		corePtr->m_Window = SDL_CreateWindow("My Engine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			corePtr->m_Screen->getWidth(), corePtr->m_Screen->getHeight(),
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		/// Checks to see if an OpenGL context has been created for the window
		/// If it hasn't been created it will then throw an exception
		if (!SDL_GL_CreateContext(corePtr->m_Window))
		{
			throw std::exception();
		}

		/// Checks to see if glew has been initialized 
		/// If it hasn't been initialized it will then throw an exception
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
		
		///brief Creates an entity which is then added to a vector which is used to store all of the entities
		///it initializes the entity with knowledge of itself and a transform

		
		std::shared_ptr<Entity> entityPtr = std::make_shared<Entity>();
		entityPtr->m_Core = m_CoreSelf;
		entityPtr->m_EntitySelf = entityPtr;
		entityPtr->m_Transform = entityPtr->addComponent<Transform>();
		m_Entities.push_back(entityPtr);
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
		/// Adds a collider to the List for iteration
		m_CollidersVect.push_back(collider);
	}

	void Core::unregisterCollider(SphereCollider* collider)
	{
		///takes the given collider off the list.

		for (int i = 0; i < (int)m_CollidersVect.size(); i++)
		{
			if (m_CollidersVect[i].get() == collider)
			{
				m_CollidersVect.erase(m_CollidersVect.begin() + i);
				/// i-- ensures we dont miss one when iterating
				i--;
			}
		}
	}

	void Core::registerConvexCollider(std::shared_ptr<myengine::ConvexCollider> convexCollider)
	{
		/// Adds a collider to the List for iteration
		m_ConvexCollidersVect.push_back(convexCollider);
	}

	void Core::unregisterConvexCollider(ConvexCollider* convexCollider)
	{
		///takes the given collider off the list.
		for (int i = 0; i < (int)m_ConvexCollidersVect.size(); i++)
		{
			if (m_ConvexCollidersVect[i].get() == convexCollider)
			{
				m_ConvexCollidersVect.erase(m_ConvexCollidersVect.begin() + i);
				/// i-- ensures we dont miss one when iterating
				i--;
			}
		}
	}


	void Core::start()
	{

		
		///brief Runs the main game loop.
		///From there it will then run tick and display functions to show all of the entities created
		m_Running = true;
		while (m_Running)
		{
			SDL_Event incomingEvent;
			///checks for SDL Eventslike keystrokes.
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

			/// Loop through all Sphere colliders check if they are sphere-sphere hits and process.
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
			/// Loop through all Convex colliders check if they are convex-sphere hits and process.
			for (size_t ci = 0; ci < m_ConvexCollidersVect.size(); ci++)
			{
				for (size_t sj = 0; sj < m_CollidersVect.size(); sj++)
				{
					m_ConvexCollidersVect[ci]->isColliding(m_CollidersVect[sj]);
				}
			}
			///Loop through the entities and call their on tick function
			for (size_t ei = 0; ei < m_Entities.size(); ++ei)
			{
				m_Entities.at(ei)->tick();
			}
			///environment is not an entity so needs ticking manually
			m_Environment->tick();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			/// Tests for entity destruction and destroys if needed
			for (size_t ei = 0; ei < m_Entities.size(); ++ei)
			{
				if (m_Entities.at(ei)->m_DestroyMe == true)
				{
					removeEntity(m_Entities.at(ei));

					ei--;
				}

			}
			///Draws all entities on screen
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
		///Stopps Core from running
		m_Running = false;
	}
	void Core::flushCore()
	{
		
		while (m_CollidersVect.size() > 0)
		{
			m_CollidersVect[0]->onDestroy();
		}
		while (m_ConvexCollidersVect.size() > 0)
		{
			m_ConvexCollidersVect[0]->onDestroy();
		}
		///Clears the core of all entities
		while (m_Entities.size() > 0)
		{
			m_Entities.erase(m_Entities.begin());
		}
		
	}

	void Core::removeEntity(std::shared_ptr<Entity> deleteentity)
	{
		///Destroys and removes the entity given
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
		///able to get an entity by the name provided in the level file.
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