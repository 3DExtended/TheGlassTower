#include "AScene.h"

namespace engine
{
	AScene::AScene()
	{
	}
	AScene::~AScene()
	{
	}
	void AScene::setGame(AGame * game)
	{
		m_game = game;
	}
	AGame * AScene::getGame()
	{
		return m_game;
	}
	void AScene::s_update()
	{

		update(); // FOR TESTING
	}
	void AScene::s_render()
	{

		render(); // FOR TESTING
	}
	void AScene::s_create()
	{
		// Scene Create

		// Pass
		create();
	}
	void AScene::s_destroy()
	{
		// Pass
		destroy();
		// Scene Destroy

	}
}