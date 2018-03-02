#include "SceneTest.h"
#include "GOCapsule.h"
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
	addGameObject(new GOCapsule());
	addGameObject(new GOSphere());
	addGameObject(new GOPlane());
}
void SceneTest::destroy()
{
}
