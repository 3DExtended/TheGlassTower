// TheGlassTower.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <tchar.h>	//Other entry point for windows
#include "stdafx.h"
#include <iostream>
#include "Engine/Display.h"
#include "Engine/Input.h"

using namespace ENGINE;

class ENGINE::EngineClass {
public:
	static void RunEngine() {
		Display* display = new Display(800, 600, "The Glass Tower");

		std::cout << "Test" << std::endl;
		bool isRunning = true;
		SDL_Event e;

		//main loop of gameengine
		while (isRunning) {
			//pull sdl events (Key and mouse events, quit event etc.)
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {	//Quit event is triggered after hitting the red X in the upper right corner
					isRunning = false;
				}
				else if (e.type == SDL_KEYDOWN) {
					Input::SetKeyState(e.key.keysym.scancode, true);
				}
				else if (e.type == SDL_KEYUP) {
					Input::SetKeyState(e.key.keysym.scancode, false);
				}
				else if (e.type == SDL_MOUSEBUTTONUP) {
					Input::SetButtonState(e.button.button, false);
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN) {
					Input::SetButtonState(e.button.button, true);
				}
				else if (e.type == SDL_MOUSEMOTION) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					Input::SetMousePosition(x, y);
				}
			}

			//Update gameState
			 //sceneHandler->Update();

			//clear old buffer so we can render on it
			 //display->ClearBuffer();

			//Render Game
			 //sceneHandler->Render();

			//render text
			 //FontHandler::RenderAllFonts();

			//swap buffer
			display->SwapBuffer();
		}
	}
};

using namespace ENGINE;
int _tmain(int argc, _TCHAR* argv[]) {
	//ENGINE::Run(0);
	ENGINE::EngineClass::RunEngine();
	return 0;
}
