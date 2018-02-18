#pragma once
#include "AGame.h"
#include "Display.h"
#include "Input.h"
//#include "PhysX/PxPhysicsAPI.h"
#include <vector>
#include <mutex>

namespace engine
{
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

	private:

		// initialized
		bool m_initialized = false;

		// game Thread
		void gameThread(AGame * game);

		// game lists
		std::vector<AGame *> m_games;
		std::mutex m_gameLock;
	};
}