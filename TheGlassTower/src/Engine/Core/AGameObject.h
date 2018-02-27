#pragma once
#include "AScene.h"

namespace engine
{
	class AGameObject
	{
		friend class AScene;
	public:
		// Constructor
		AGameObject();
		virtual ~AGameObject();

		// Get Scene
		AScene * getScene();
	private:
		// Scene Instance
		AScene * m_scene;

		// Create and Destroy
		virtual void create() = 0;
		virtual void destroy() = 0;

		// Pre PhysX
		virtual void preUpdate() {};
		// During PhysX
		virtual void update() {};
		// Post PhysX
		virtual void postUpdate() {};

		virtual void render() {}; // REMOVE ME
	};
}