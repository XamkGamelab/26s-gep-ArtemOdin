#include "input_system.hpp"
#include <SDL3/SDL_events.h>


auto gep::input::input_system::ProcessEvent(const SDL_Event& event) noexcept -> void
{
	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:
		pressedDown.insert(event.key.key);
		pressedNow.insert(event.key.key);
		break;
	case SDL_EVENT_KEY_UP:
		pressedUp.insert(event.key.key);
		pressedNow.erase(event.key.key);
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		mousePressedDown.insert(event.button.button);
		mousePressedNow.insert(event.button.button);
		break;
	case SDL_EVENT_MOUSE_BUTTON_UP:
		mousePressedUp.insert(event.button.button);
		mousePressedNow.erase(event.button.button);
		break;
	}
	
}


auto gep::input::input_system::Update() noexcept -> void
{
	Clear();
}

auto gep::input::input_system::Clear() noexcept -> void
{
	pressedDown.clear();
	pressedUp.clear();
	mousePressedDown.clear();
	mousePressedUp.clear();

};

auto gep::input::input_system::IsKeyDown(SDL_Keycode key) const noexcept -> bool
{
	return pressedDown.contains(key);
}

auto gep::input::input_system::IsKeyUp(SDL_Keycode key) const noexcept -> bool
{
	return pressedUp.contains(key);
}

auto gep::input::input_system::IsKeyPressed(SDL_Keycode key) const noexcept -> bool
{
	return pressedNow.contains(key);
}

auto gep::input::input_system::IsMouseDown(unsigned int mouseBtnIdx) const noexcept -> bool
{
	return mousePressedDown.contains(mouseBtnIdx);
}

auto gep::input::input_system::IsMouseUp(unsigned int mouseBtnIdx) const noexcept -> bool
{
	return mousePressedUp.contains(mouseBtnIdx);
}

auto gep::input::input_system::IsMousePressed(unsigned int mouseBtnIdx) const noexcept -> bool
{
	return mousePressedNow.contains(mouseBtnIdx);
}