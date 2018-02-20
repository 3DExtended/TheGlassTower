#include "GameTest.h"

GameTest::GameTest()
{
}
GameTest::~GameTest()
{
}
void GameTest::create()
{
	m_scene = new SceneTest();
	m_scene->setGame(this);
	m_scene->s_create();
}
void GameTest::destroy()
{
	m_scene->s_destroy();
	delete m_scene;
}	
void GameTest::update()
{
	m_scene->s_update();
}
void GameTest::render()
{
	m_scene->s_render();
}