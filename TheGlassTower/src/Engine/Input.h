#pragma once
#include <stdint.h>

namespace engine {
	class Input {
		friend class Engine;
	public:
		// Sichert sich Speicher f�r Key und Button States
		Input();
		// Gibt Speicher frei
		~Input();

		// Key State Abfragen
		bool isKeyDown(int32_t scanCode);
		bool isKeyUp(int32_t scanCode);
		bool isKeyPressed(int32_t scanCode);
		bool isKeyReleased(int32_t scanCode);

		// Button State Abfragen
		bool isButtonDown(int32_t scanCode);
		bool isButtonUp(int32_t scanCode);
		bool isButtonPressed(int32_t scanCode);
		bool isButtonReleased(int32_t scanCode);

		// Mouse Position Abfragen
		int32_t getMousePositionX();
		int32_t getMousePositionY();

		// Mouse Speed Abfragen
		int32_t getMouseSpeedX();
		int32_t getMouseSpeedY();

		// Mouse Scroll Abfragen
		int32_t getMouseScrollX();
		int32_t getMouseScrollY();

	private:
		// Mouse Position
		int32_t m_mousePosX;
		int32_t m_mousePosY;

		// Mouse Speed
		int32_t m_mouseSpeedX;
		int32_t m_mouseSpeedY;

		// Mouse Scroll
		int32_t m_mouseScrollX;
		int32_t m_mouseScrollY;

		// Key States
		bool * m_keyIsDown;
		bool * m_keyIsEvent;

		// Button States
		bool * m_buttonIsDown;
		bool * m_buttonIsEvent;

		// Input Handling
		void setKeyState(int32_t scanCode, bool isDown);
		void setButtonState(int32_t scanCode, bool isDown);
		void setMousePosition(int32_t x, int32_t y);
		void setMouseScroll(int32_t x, int32_t y);

		// Pre und Post
		void inputPreUpdate();
		void inputPostUpdate();
	};
}