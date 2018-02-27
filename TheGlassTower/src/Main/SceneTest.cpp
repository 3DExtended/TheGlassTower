#include "SceneTest.h"
#include "GOSphere.h"
#include "GOPlane.h"

SceneTest::SceneTest()
{
}
SceneTest::~SceneTest()
{
}
void SceneTest::create()
{
	addGameObject(new GOSphere());
	addGameObject(new GOPlane());
}
void SceneTest::destroy()
{
}
