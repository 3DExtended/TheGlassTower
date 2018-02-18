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
			// SetUp
			glewExperimental = GL_TRUE;
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			{
				m_initialized = false;
				std::cerr << "Could not init SDL2. Received following error: " << SDL_GetError() << std::endl;
			}
			else
			{
				m_initialized = true;
				std::cout << "Successfully init SDL2" << std::endl;
			}
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
			// TearDown
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
		game->ag_create();

		// Main Loop
		while (game->m_input->isRunning()) {
			// Input
			game->m_input->update();

			// Update
			game->ag_update();

			// Clear
			game->m_display->clearBuffer();

			// Render
			game->ag_render();

			// Swap
			game->m_display->swapBuffer();
		}

		// TearDown
		game->ag_destroy();
		delete game->m_input;
		delete game->m_display;
		game->m_done = true;
	}
}