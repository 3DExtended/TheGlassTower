// TheGlassTower.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <tchar.h>	//Other entry point for windows
#include "stdafx.h"
#include <iostream>
#include "Engine/Display.h"
#include "Engine/Input.h"

using namespace engine;

class engine::Engine {
public:
	static void RunEngine() {
		Display* display = new Display(800, 600, "The Glass Tower");
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
};

using namespace engine;
int _tmain(int argc, _TCHAR* argv[]) {
	//ENGINE::Run(0);
	engine::Engine::RunEngine();
	return 0;
}
