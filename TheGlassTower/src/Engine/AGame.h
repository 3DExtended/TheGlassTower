#pragma once
#include "Input.h"
#include "Display.h"
#include <thread>

namespace engine
{
	class AGame
	{
		friend class Engine;
	public:
		AGame();
		virtual ~AGame();

		virtual void create() = 0;
		virtual void destroy() = 0;



	private:
		// Game Methods
		void ag_update();
		void ag_render();

		// Display
		Display * display;

		// Input
		Input * input;

		// Thread
		std::thread * thread;
		bool done = false;
	};
}