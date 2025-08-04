#pragma once
#include "../Math/Vector2.h"

#include <vector>
#include <array>

namespace bacon {
	class InputSystem {
	public:
		enum class MouseButton : uint8_t {
			Left,
			Right,
			Middle
		};

	public:
		InputSystem() = default;

		bool Initialize();
		void Kill();

		void Update();

		//Keyboard input
		bool GetKeyDown(uint8_t key) const { return m_keyboardState[key]; }
		bool GetPrevKeyDown(uint8_t key) const { return m_prevKeyboardState[key]; }
		bool GetKeyPressed(uint8_t key) const { return !m_prevKeyboardState[key] && m_keyboardState[key]; }
		bool GetKeyReleased(uint8_t key) const { return m_prevKeyboardState[key] && !m_keyboardState[key]; }

		//Mouse input
		bool GetMouseButtonDown(uint8_t button) { return m_mouseButtonState[(uint8_t)button]; }
		bool GetPrevMouseButtonDown(uint8_t button) { return m_prevMouseButtonState[(uint8_t)button]; }
		bool GetMouseButtonPressed(uint8_t button) { return !m_prevMouseButtonState[(uint8_t)button] && m_mouseButtonState[(uint8_t)button]; }
		bool GetPrevMouseButtonPressed(uint8_t button) { return m_prevMouseButtonState[(uint8_t)button] && !m_mouseButtonState[(uint8_t)button]; }

		const vec2& GetMousePosition() const { return m_mousePosition; }
		const vec2& GetPrevMoustPosition() const { return m_prevMousePosition; }

	private:
		std::vector<bool> m_keyboardState;
		std::vector<bool> m_prevKeyboardState;

		bacon::vec2 m_mousePosition {0,0};
		bacon::vec2 m_prevMousePosition{ 0,0 };

		std::array<bool, 3> m_mouseButtonState{ false, false, false };
		std::array<bool, 3> m_prevMouseButtonState{ false, false, false };
	};
}