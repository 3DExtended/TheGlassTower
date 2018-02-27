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
	Engine * AGame::getEngine()
	{
		return m_engine;
	}
}