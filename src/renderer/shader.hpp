#pragma once
#include <string_view>
#include <cstdint>
#include <iostream>

namespace gep::renderer
{
	class [[nodiscard]] shader
	{
	public:
		shader() = default;
		~shader();
		shader(std::string_view v_path, std::string_view f_path);

		auto get_id() const noexcept -> uint32_t { return id; }
		auto bind() const noexcept -> void;
		auto clear() -> void;

		shader(const shader&) = delete;
		shader& operator=(const shader&) = delete;

		shader(shader&& rhs) noexcept;
		shader& operator=(shader&& rhs) noexcept;

		auto set_int(const std::string& name, uint32_t value) const -> void;
		auto set_matrix(const std::string& name, const float* value) const -> void;

	private:
		uint32_t id{ 0 };

		auto compile_shader(uint32_t shader, const char* source) const -> bool;
	};
}