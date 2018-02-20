#include "Engine.h"
#include <SDL2/SDL.h>
#include <chrono>

namespace engine
{
	Engine::Engine()
	{
	}
	Engine::~Engine()
	{
	}
	void Engine::initialize()
	{
		if (!m_initialized)
		{
			// SetUp SDL
			glewExperimental = GL_TRUE;
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			{
				std::cerr << "Could not init SDL2. Received following error: " << SDL_GetError() << std::endl;
				return;
			}
			// SetUp PhysX Callbacks
			m_pxDefaultAllocatorCallback = physx::PxDefaultAllocator();
			m_pxDefaultErrorCallback = physx::PxDefaultErrorCallback();
			// SetUp PhysX Foundation
			m_pxFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, m_pxDefaultAllocatorCallback, m_pxDefaultErrorCallback);
			if (!m_pxFoundation)
			{
				std::cerr << "Could not init PhysX Foundation." << std::endl;
				return;
			}
			// SetUp PhysX
			bool recordMemoryAllocations = true;
			m_pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, * m_pxFoundation, physx::PxTolerancesScale(), recordMemoryAllocations);
			if (!m_pxPhysics)
			{
				std::cerr << "Could not init PhysX." << std::endl;
				return;
			}
			// SetUp PhysX Cooking
			m_pxCooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_pxFoundation, physx::PxCookingParams(physx::PxTolerancesScale()));
			if (!m_pxCooking)
			{
				std::cerr << "Could not init PhysX Cooking." << std::endl;
				return;
			}
			// SetUp PhysX Extensions
			if (!PxInitExtensions(*m_pxPhysics, nullptr))
			{
				std::cerr << "Could not init PhysX Extensions." << std::endl;
				return;
			}
			// Done
			m_initialized = true;
		}
	}
	void Engine::terminate()
	{
		if (m_initialized)
		{
			while (true)
			{
				// Erase
				m_gameLock.lock();
				for (auto it = m_games.begin(); it != m_games.end(); it++)
				{
					if ((*it)->m_done)
					{
						delete (*it);
						m_games.erase(it);
						break;
					}
				}
				// Break
				if (m_games.size() == 0)
				{
					m_initialized = false;
					m_gameLock.unlock();
					break;
				}
				m_gameLock.unlock();
				// Thread has done some work and is tired now
				{
					using namespace std::chrono_literals;
					std::this_thread::sleep_for(100ms);
				}
			}
			// TearDown Extensions
			PxCloseExtensions();
			// TearDown Cooking
			m_pxCooking->release();
			// TearDown PhysX
			m_pxPhysics->release();
			// TearDown PhysX Foundation
			m_pxFoundation->release();
			// TearDown SDL
			SDL_Quit();
		}
	}
	void Engine::runGame(AGame * game)
	{
		// Check if engine is initialized
		m_gameLock.lock();
		if (!m_initialized)
		{
			m_gameLock.unlock();
			return;
		}
		
		// Start thread
		game->m_thread = new std::thread(&engine::Engine::gameThread, this, game);
		m_games.push_back(game);
		m_gameLock.unlock();
	}
	void Engine::gameThread(AGame * game)
	{
		// SetUp
		game->m_display = new Display(800, 600, "The Glass Tower");
		game->m_input = new Input();
		game->create();

		// Main Loop
		while (game->m_input->isRunning()) {
			// Input
			game->m_input->update();

			// Update
			game->update();

			// Clear
			game->m_display->clearBuffer();

			// Render
			game->render();

			// Swap
			game->m_display->swapBuffer();
		}

		// TearDown
		game->destroy();
		delete game->m_input;
		delete game->m_display;
		game->m_done = true;
	}
}