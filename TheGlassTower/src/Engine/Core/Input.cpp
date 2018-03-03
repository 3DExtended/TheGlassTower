#include "Input.h"
#include "SDL2\SDL.h"
#include <iostream>

namespace engine
{
	Input::Input()
	{
		m_keyIsDown = (bool*)malloc(SDL_NUM_SCANCODES * sizeof(bool));
		m_keyIsEvent = (bool*)malloc(SDL_NUM_SCANCODES * sizeof(bool));
		m_buttonIsDown = (bool*)malloc(8 * sizeof(bool));
		m_buttonIsEvent = (bool*)malloc(8 * sizeof(bool));
	}
	Input::~Input()
	{
		free(m_buttonIsEvent);
		free(m_buttonIsDown);
		free(m_keyIsEvent);
		free(m_keyIsDown);
	}
	bool Input::isKeyDown(int32_t scanCode)
	{
		return m_keyIsDown[scanCode];
	}
	bool Input::isKeyUp(int32_t scanCode)
	{
		return !m_keyIsDown[scanCode];
	}
	bool Input::isKeyPressed(int32_t scanCode)
	{
		return m_keyIsDown[scanCode] && m_keyIsEvent;
	}
	bool Input::isKeyReleased(int32_t scanCode)
	{
		return (!m_keyIsDown[scanCode]) && m_keyIsEvent;
	}
	bool Input::isButtonDown(int32_t scanCode)
	{
		return m_buttonIsDown[scanCode];
	}
	bool Input::isButtonUp(int32_t scanCode)
	{
		return !m_buttonIsDown[scanCode];
	}
	bool Input::isButtonPressed(int32_t scanCode)
	{
		return m_buttonIsDown[scanCode] && m_buttonIsEvent[scanCode];
	}
	bool Input::isButtonReleased(int32_t scanCode)
	{
		return (!m_buttonIsDown[scanCode]) && m_buttonIsEvent[scanCode];
	}
	int32_t Input::getMousePositionX()
	{
		return m_mousePosX;
	}
	int32_t Input::getMousePositionY()
	{
		return m_mousePosY;
	}
	int32_t Input::getMouseSpeedX()
	{
		return m_mouseSpeedX;
	}
	int32_t Input::getMouseSpeedY()
	{
		return m_mouseSpeedY;
	}
	int32_t Input::getMouseScrollX()
	{
		return m_mouseScrollX;
	}
	int32_t Input::getMouseScrollY()
	{
		return m_mouseScrollY;
	}
	bool Input::isRunning()
	{
		return m_isRunning;
	}
	float Input::getDelta()
	{
		return m_delta;
	}
	void Input::setKeyState(int32_t scanCode, bool isDown)
	{
		m_keyIsDown[scanCode] = isDown;
		m_keyIsEvent[scanCode] = true;
	}
	void Input::setButtonState(int32_t scanCode, bool isDown)
	{
		m_buttonIsDown[scanCode] = isDown;
		m_buttonIsEvent[scanCode] = true;
	}
	void Input::setMousePosition(int32_t x, int32_t y)
	{
		m_mouseSpeedX = x - m_mousePosX;
		m_mousePosX = x;
		m_mouseSpeedY = y - m_mousePosY;
		m_mousePosY = y;
	}
	void Input::setMouseScroll(int32_t x, int32_t y)
	{
		m_mouseScrollX = x;
		m_mouseScrollY = y;
	}
	void Input::update()
	{
		// Prepare
		for (uint32_t i = 0; i < SDL_NUM_SCANCODES; i++)
		{
			m_keyIsEvent[i] = false;
		}
		for (uint32_t i = 0; i < 8; i++)
		{
			m_buttonIsEvent[i] = false;
		}
		m_mouseSpeedX = 0;
		m_mouseSpeedY = 0;
		m_mouseScrollX = 0;
		m_mouseScrollY = 0;

		// Delta
		m_now = SDL_GetTicks();
		m_delta = ((float)(m_now - m_last)) / 1000.0f;
		m_last = m_now;
		if (m_delta <= 0.015f || m_delta >= 0.017f)
			m_delta = 0.016f;

		// Event Handling
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				m_isRunning = false;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				setKeyState(event.key.keysym.scancode, true);
			}
			else if (event.type == SDL_KEYUP)
			{
				setKeyState(event.key.keysym.scancode, false);
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				setButtonState(event.button.button, false);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				setButtonState(event.button.button, true);
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				setMousePosition(event.motion.x, event.motion.y);
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				setMouseScroll(event.wheel.x, event.wheel.y);
			}
		}
	}
}