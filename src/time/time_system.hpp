#pragma once


#include <iostream>
#include <chrono>

namespace gep::time
{

	class [[nodiscard]] time_system
	{
	public:
		static auto instance() -> time_system& {
			static time_system static_instance;
			return static_instance;
		}

		time_system(const time_system&) = delete;
		time_system(time_system&&) = delete;
		time_system operator=(const time_system&) = delete;
		time_system operator=(const time_system&&) = delete;

		auto Init() noexcept -> void;
		auto Tick() noexcept -> void;
		auto GetDeltaTime() const noexcept -> float;

	private:
		time_system() = default;
		~time_system() = default;

		float deltaTime = 0;
		std::chrono::steady_clock::time_point lastTime;
		std::chrono::steady_clock::time_point nowTime;

	};
}