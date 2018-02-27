#pragma once
#include "Display.h"
#include "Input.h"
#include "PhysX/PxPhysicsAPI.h"
#include <vector>
#include <mutex>

namespace engine
{
	class AGame;
	class Engine
	{
	public:
		// construct and deconstruct
		Engine();
		~Engine();

		// initialize and terminate
		void initialize();
		void terminate();

		// run game
		void runGame(AGame * game);

		// PhysX
		physx::PxPhysics * getPhysics();
	private:

		// initialized
		bool m_initialized = false;

		// game Thread
		void gameThread(AGame * game);

		// game lists
		std::vector<AGame *> m_games;
		std::mutex m_gameLock;

		// PhysX
		physx::PxDefaultErrorCallback m_pxDefaultErrorCallback;
		physx::PxDefaultAllocator m_pxDefaultAllocatorCallback;
		physx::PxFoundation * m_pxFoundation;
		physx::PxPhysics * m_pxPhysics;
		physx::PxCooking * m_pxCooking;
	};
}