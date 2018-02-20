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
		// ADD GameObject
		addGameObject();
		// REM GameObject
		remGameObject();
		// Pre Update
		sgo_preUpdate();
		// Update
		sgo_update();
		// Post Update
		sgo_postUpdate();
		// FOR TESTING
		update();
	}
	void AScene::s_render()
	{

		// FOR TESTING
		render();
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
	void AScene::sgo_preUpdate()
	{
		for (auto it : m_gameObjects)
		{
			it->preUpdate();
		}
	}
	void AScene::sgo_update()
	{
		for (auto it : m_gameObjects)
		{
			it->update();
		}
	}
	void AScene::sgo_postUpdate()
	{
		for (auto it : m_gameObjects)
		{
			it->postUpdate();
		}
	}
	void AScene::addGameObject(AGameObject * obj)
	{
		m_gameObjectAddLock.lock();
		m_gameObjectAdd.push_back(obj);
		m_gameObjectAddLock.unlock();
	}
	void AScene::addGameObject()
	{
		bool add = true;
		while (add)
		{
			if (m_gameObjectAddLock.try_lock())
			{
				size_t addCount = m_gameObjectAdd.size();
				if (addCount > 0)
				{
					AGameObject * obj = m_gameObjectAdd.back();
					m_gameObjectAdd.pop_back();
					m_gameObjectAddLock.unlock();
					m_gameObjects.push_back(obj);
					obj->m_scene = this;
					obj->create();
				}
				else
				{
					m_gameObjectAddLock.unlock();
					add = false;
				}
			}
			else
			{
				add = false;
			}
		}
	}
	void AScene::remGameObject(AGameObject * obj)
	{
		m_gameObjectRemLock.lock();
		m_gameObjectRem.push_back(obj);
		m_gameObjectRemLock.unlock();
	}
	void AScene::remGameObject()
	{
		bool rem = true;
		while (rem)
		{
			if (m_gameObjectRemLock.try_lock())
			{
				size_t remCount = m_gameObjectRem.size();
				if (remCount > 0)
				{
					AGameObject * obj = m_gameObjectRem.back();
					m_gameObjectRem.pop_back();
					m_gameObjectRemLock.unlock();
					auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), obj);
					if (it != m_gameObjects.end())
					{
						obj->destroy();
						delete obj;
						m_gameObjects.erase(it);
					}
					else
					{
						printf("Object not found!");
					}
				}
				else
				{
					m_gameObjectRemLock.unlock();
					rem = false;
				}
			}
			else
			{
				rem = false;
			}
		}
	}
}