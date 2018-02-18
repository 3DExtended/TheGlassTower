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
		// Constructor
		AGame();
		virtual ~AGame();

		// Some Init Functions
		virtual void create() = 0;
		virtual void destroy() = 0;

		// Some Loop Functions
		virtual void update() = 0;
		virtual void render() = 0;

	private:
		// Game Methods
		void ag_create();
		void ag_destroy();
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