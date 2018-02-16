#include "Input.h"
#include "SDL2\SDL.h"

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
	bool Input::isKeyDown(int scanCode)
	{
		return m_keyIsDown[scanCode];
	}
	bool Input::isKeyUp(int scanCode)
	{
		return !m_keyIsDown[scanCode];
	}
	bool Input::isKeyPressed(int scanCode)
	{
		return m_keyIsDown[scanCode] && m_keyIsEvent;
	}
	bool Input::isKeyReleased(int scanCode)
	{
		return (!m_keyIsDown[scanCode]) && m_keyIsEvent;
	}
	bool Input::isButtonDown(int scanCode)
	{
		return m_buttonIsDown[scanCode];
	}
	bool Input::isButtonUp(int scanCode)
	{
		return !m_buttonIsDown[scanCode];
	}
	bool Input::isButtonPressed(int scanCode)
	{
		return m_buttonIsDown[scanCode] && m_buttonIsEvent[scanCode];
	}
	bool Input::isButtonReleased(int scanCode)
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
	void Input::inputPreUpdate()
	{
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
	}
	void Input::inputPostUpdate()
	{
	}
}