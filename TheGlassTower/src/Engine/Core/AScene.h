#pragma once
#include "AGame.h"
#include "Engine/Physic/PScene.h"
#include <vector>
#include <mutex>

namespace engine
{
	class AGameObject;
	class AScene
	{
	public:
		// Construct and Deconstruct
		AScene();
		virtual ~AScene();

		// Loop Methods
		void s_update();
		void s_render();

		// Create and Destroy
		void s_create();
		void s_destroy();

		// Get and Set Game
		void setGame(AGame * game);
		AGame * getGame();

		// Get PScene
		PScene * getPScene();
	private:
		// Game Instance
		AGame * m_game;

		// Physic
		PScene * m_pScene;

		// Create and Destroy
		virtual void create() = 0;
		virtual void destroy() = 0;

		// Game Objects
		std::vector<AGameObject *> m_gameObjects;
		void sgo_preUpdate();
		void sgo_update();
		void sgo_postUpdate();
		// Add GameObjects
	public:
		void addGameObject(AGameObject * obj);
	private:
		void addGameObject();
		std::mutex m_gameObjectAddLock;
		std::vector<AGameObject *> m_gameObjectAdd;
		// Rem GameObjects
	public:
		void remGameObject(AGameObject * obj);
	private:
		void remGameObject();
		std::mutex m_gameObjectRemLock;
		std::vector<AGameObject *> m_gameObjectRem;
	};
}