#pragma once
#include "PhysX/PxPhysicsAPI.h"

namespace engine
{
	class Engine;
	class PScene
	{
		friend class AScene;
	public:
		// Construct and Deconstruct
		PScene();
		~PScene();

		// Create and Destroy
		void create();
		void destroy();

		// Step Simulation
		void step(const float & delta);

		// Fetch Results
		void fetch();

	private:
		// Engine
		Engine * m_engine;

	public:
		// PhysX Scene
		physx::PxScene * m_pxScene;
	};
}