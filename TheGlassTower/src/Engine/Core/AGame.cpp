#include "AGame.h"

namespace engine
{
	AGame::AGame()
	{
	}
	AGame::~AGame()
	{
	}
	Input * AGame::getInput()
	{
		return m_input;
	}
	void AGame::ag_create()
	{
		create();
	}
	void AGame::ag_destroy()
	{
		destroy();
	}
	void AGame::ag_update()
	{
		update();
	}
	void AGame::ag_render()
	{
		render();
	}
}