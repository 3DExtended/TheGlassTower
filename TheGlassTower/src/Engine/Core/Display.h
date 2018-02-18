#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>	
#include <stdint.h>

namespace engine {
	class Display
	{
		friend class Engine;
	public:
		// display size
		void setWidth(int32_t width);
		int32_t getWidth();
		void setHeight(int32_t height);
		int32_t getHeight();
		void setSize(int32_t width, int32_t height);

		// display title
		void setTitle(std::string title);
		std::string getTitle();

	private:
		// create display
		Display(int32_t width, int32_t height, std::string title);

		// destroy display
		~Display();
		// clears backbuffer
		void clearBuffer();

		// swaps back and frontbuffer
		void swapBuffer();

		// width and height of window
		int32_t m_width;
		int32_t m_height;

		// window title
		std::string m_title;

		// the OpenGL context needed to work with the GPU
		SDL_GLContext m_glContext;

		// the window handler by SDL2
		SDL_Window * m_window;
	};
}
