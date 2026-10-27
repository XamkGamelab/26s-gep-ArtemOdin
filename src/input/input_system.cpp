#include "input_system.hpp"
#include <SDL3/SDL_events.h>

auto gep::input::input_system::update() noexcept -> void
{
	keysDown.clear();
	keysUp.clear();
	mouseDown.clear();
	mouseUp.clear();
}

auto gep::input::input_system::process_input(const SDL_Event& ev) noexcept -> void
{
	auto keycode = ev.key.key;
	auto mouse_button_index = ev.button.button;
	switch (ev.type)
	{
	case SDL_EVENT_KEY_DOWN:
		keysDown.insert(keycode);
		keysPressed.insert(keycode);
		break;
	case SDL_EVENT_KEY_UP:
		keysUp.insert(keycode);
		keysPressed.erase(keycode);
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		mouseDown.insert(mouse_button_index);
		mousePressed.insert(mouse_button_index);
		break;
	case SDL_EVENT_MOUSE_BUTTON_UP:
		mouseUp.insert(mouse_button_index);
		mousePressed.erase(mouse_button_index);
		break;
	default: break;
	}
}

auto gep::input::input_system::is_key_down(uint32_t keycode) const noexcept -> bool
{
	return keysDown.contains(keycode);
}

auto gep::input::input_system::is_key_pressed(uint32_t keycode) const noexcept -> bool
{
	return keysPressed.contains(keycode);
}

auto gep::input::input_system::is_key_up(uint32_t keycode) const noexcept -> bool
{
	return keysUp.contains(keycode);
}

auto gep::input::input_system::is_mouse_down(uint8_t mouse_button_index) const noexcept -> bool
{
	return mouseDown.contains(mouse_button_index);
}

auto gep::input::input_system::is_mouse_pressed(uint8_t mouse_button_index) const noexcept -> bool
{
	return mousePressed.contains(mouse_button_index);
}

auto gep::input::input_system::is_mouse_up(uint8_t mouse_button_index) const noexcept -> bool
{
	return mouseUp.contains(mouse_button_index);
}