#include "Display.h"

namespace engine
{
	Display::Display(int32_t width, int32_t height, std::string title)
		: m_width(width), m_height(height), m_title(title)
	{
		glewExperimental = GL_TRUE;
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cerr << "Could not init SDL2. Received following error: " << SDL_GetError() << std::endl;
		}
		else {
			std::cout << "Successfully init SDL2" << std::endl;

			//Request modern OpenGL context and set important attributes for OpenGL
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			//create window for rendering
			m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

			//create context for OpenGL
			m_glContext = SDL_GL_CreateContext(m_window);

			//init glew
			GLenum res = glewInit();
			if (res != GLEW_OK) {
				std::cerr << "Glew failed to init..." << std::endl;
			}
			else {
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);


				//print OpenGL versions
				std::cout << "----------" << std::endl;
				std::cout << "OpenGL is loaded:" << std::endl;
				std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
				std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
				std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
				std::cout << "----------" << std::endl;
			}

		}
	}
	Display::~Display()
	{
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
	void Display::clearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void Display::swapBuffer()
	{
		SDL_GL_SwapWindow(m_window);
	}
	void Display::setWidth(int32_t width)
	{
		setSize(width, m_height);
	}
	int32_t Display::getWidth()
	{
		return m_width;
	}
	void Display::setHeight(int32_t height)
	{
		setSize(m_width, height);
	}
	int32_t Display::getHeight()
	{
		return m_height;
	}
	void Display::setSize(int32_t width, int32_t height)
	{
		m_width = width;
		m_height = height;
		SDL_SetWindowSize(m_window, m_width, m_height);
	}
	void Display::setTitle(std::string title)
	{
		m_title = title;
		SDL_SetWindowTitle(m_window, m_title.c_str());
	}
	std::string Display::getTitle()
	{
		return m_title;
	}
}