#include "AGameObject.h"

namespace engine
{
	AGameObject::AGameObject()
	{
	}
	AGameObject::~AGameObject()
	{
	}
	AScene * AGameObject::getScene()
	{
		return m_scene;
	}
}