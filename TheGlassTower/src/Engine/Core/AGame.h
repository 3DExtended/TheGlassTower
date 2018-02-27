#pragma once
#include "Input.h"
#include "Display.h"
#include "Engine.h"
#include <thread>

namespace engine
{
	class AGame
	{
		friend class Engine;
	public:
		// Constructor
		AGame();
		virtual ~AGame();

		// Some Init Functions
		virtual void create() = 0;
		virtual void destroy() = 0;

		// Some Loop Functions
		virtual void update() = 0;
		virtual void render() = 0;

		// Get Input
		Input * getInput();
		// Get Engine
		Engine * getEngine();
	private:
		// Engine
		Engine * m_engine;

		// Display
		Display * m_display;

		// Input
		Input * m_input;

		// Thread
		std::thread * m_thread;
		bool m_done = false;
	};
}