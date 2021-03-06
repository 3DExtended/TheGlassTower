// TheGlassTower.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <tchar.h>	//Other entry point for windows
#include "Engine/Core/Engine.h"
#include "GameTest.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// initialize engine
	engine::Engine * engine = new engine::Engine();
	engine->initialize();

	// run game
	engine->runGame(new GameTest());

	// terminate engine
	engine->terminate();
	delete engine;

	// exit
	return 0;
}
