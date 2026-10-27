#include "shader.hpp"
#include "..\core\file_loader.hpp"
#include <glad/gl.h>
#include <optional>
#include <utility>

namespace gep::renderer
{
	shader::shader(std::string_view v_path, std::string_view f_path)
	{
		uint32_t vertexShader, fragmentShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		auto vertex_source = core::load_text_file(v_path);
		if (!vertex_source.has_value())
		{
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Could not read vertex shader's code");
			return;
		}

		auto success = compile_shader(vertexShader, vertex_source.value().c_str());

		if (!success)
		{
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Could not compile vertex shader");
			return;
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		auto frag_source = core::load_text_file(f_path);
		if (!frag_source.has_value())
		{
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Could not read fragment shader's code");
			return;
		}

		success = compile_shader(fragmentShader, frag_source.value().c_str());

		if (!success)
		{
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Could not compile fragment shader");
			return;
		}

		// Shader program creation ---> OpenGL object
		id = glCreateProgram(); // Allocation
		// Attach shaders to the shader program
		glAttachShader(id, vertexShader);
		glAttachShader(id, fragmentShader);
		// Link shader program
		glLinkProgram(id);
		int32_t status = 0;
		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if (status == 0)
		{
			int32_t log_length;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);
			std::string log = std::string((std::size_t)log_length, ' ');
			glGetProgramInfoLog(id, log_length, nullptr, &log[0]);
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Shader program linking failed: %s", log.c_str());
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	shader::shader(shader&& rhs) noexcept : id(std::exchange(rhs.id, 0))
	{

	}

	shader::~shader()
	{
		clear();
	}

	auto shader::bind() const noexcept -> void
	{
		glUseProgram(id);
	}

	auto shader::clear() -> void
	{
		if (id != 0)
		{
			glDeleteProgram(id);
			id = 0;
		}
	}

	

	shader& shader::operator=(shader&& rhs) noexcept
	{
		if (this == &rhs)
		{
			return *this;
		}

		clear();

		id = std::exchange(rhs.id, 0);
	}

	auto shader::compile_shader(uint32_t shader, const char* source) const -> bool
	{
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		int32_t status = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != 0)
		{
			return true;
		}

		int32_t log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		std::string log = std::string((std::size_t)log_length, ' ');
		glGetShaderInfoLog(shader, log_length, nullptr, &log[0]);
		SDL_LogError(SDL_LOG_CATEGORY_GPU,
			"Frag shader compile failed: %s", log.c_str());

		return false;
	}

	auto shader::set_int(const std::string& name, uint32_t value) const -> void
	{
		const GLint location = glGetUniformLocation(id, name.c_str());

		if (location == -1) 
		{
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Int location to set to not found");
			return;
		}

		glUniform1i(location, value);
	}

	auto shader::set_matrix(const std::string& name, const float* value) const -> void
	{
		const GLint location = glGetUniformLocation(id, name.c_str());

		if (location == -1)
		{
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Matrix location to set to not found");
			return;
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, value);
	}
}