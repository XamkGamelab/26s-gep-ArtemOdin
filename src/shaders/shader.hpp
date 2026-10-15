#pragma once


#include <iostream>
#include <chrono>

namespace gep::shaders
{

	class [[nodiscard]] shader
	{
	public:
		static auto instance() -> shader& {
			static shader static_instance;
			return static_instance;
		}

		shader(const shader&) = delete;
		shader(shader&&) = delete;
		shader operator=(const shader&) = delete;
		shader operator=(const shader&&) = delete;

		auto Bind() noexcept -> void;
		auto Unbind() noexcept -> void;
		auto Delete() noexcept -> void;

		auto Load( const std::string& vertexPath, const std::string& fragmentPath) -> bool;
	private:
		shader() = default;
		~shader() = default;

		uint32_t shaderProgram = 0;

	};
}