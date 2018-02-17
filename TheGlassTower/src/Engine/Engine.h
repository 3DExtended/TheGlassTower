#pragma once

#include "Engine/Display.h"
#include "Engine/Input.h"

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
		void runGame();

	private:
		// initialized?
		bool m_initialized = false;
	};
}