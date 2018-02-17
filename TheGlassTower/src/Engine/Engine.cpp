#include "Engine.h"
#include <SDL2/SDL.h>

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
			m_initialized = false;
			SDL_Quit();
		}
	}
	void Engine::runGame()
	{
		// Check if engine is initialized
		if (!m_initialized)
		{
			return;
		}

		// SetUp
		Display * display = new Display(800, 600, "The Glass Tower");
		Input * input = new Input();

		std::cout << "Test" << std::endl;
		bool isRunning = true;
		SDL_Event e;

		//main loop of gameengine
		while (isRunning) {
			//pull sdl events (Key and mouse events, quit event etc.)
			input->inputPreUpdate();
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {	//Quit event is triggered after hitting the red X in the upper right corner
					isRunning = false;
				}
				else if (e.type == SDL_KEYDOWN) {
					input->setKeyState(e.key.keysym.scancode, true);
				}
				else if (e.type == SDL_KEYUP) {
					input->setKeyState(e.key.keysym.scancode, false);
				}
				else if (e.type == SDL_MOUSEBUTTONUP) {
					input->setButtonState(e.button.button, false);
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN) {
					input->setButtonState(e.button.button, true);
				}
				else if (e.type == SDL_MOUSEMOTION) {
					input->setMousePosition(e.motion.x, e.motion.y);
				}
				else if (e.type == SDL_MOUSEWHEEL) {
					input->setMouseScroll(e.wheel.x, e.wheel.y);
				}
			}
			input->inputPostUpdate();

			//Update gameState
			//sceneHandler->Update();

			//clear old buffer so we can render on it
			//display->ClearBuffer();

			//Render Game
			//sceneHandler->Render();

			//render text
			//FontHandler::RenderAllFonts();

			//swap buffer
			display->swapBuffer();
		}
	}
}