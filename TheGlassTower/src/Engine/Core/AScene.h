#pragma once
#include "AGame.h"

namespace engine
{
	class AScene
	{
	public:
		// Construct and Deconstruct
		AScene();
		~AScene();

		// Loop Methods
		void s_update();
		void s_render();

		// Create and Destroy
		void s_create();
		void s_destroy();

		// Get and Set Game
		void setGame(AGame * game);
		AGame * getGame();
	private:
		// Game Instance
		AGame * m_game;

		// Loop Methods
		virtual void update() = 0;
		virtual void render() = 0;

		// Create and Destroy
		virtual void create() = 0;
		virtual void destroy() = 0;

		// Game Objects


	};
}