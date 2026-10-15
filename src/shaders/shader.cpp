#include "shader.hpp"

#include <glad/gl.h>
#include <SDL3/SDL_log.h>

#include "../files/file_loader.hpp"

namespace gep::shaders
{

	auto shader::Load(const std::string& vertexPath, const std::string& fragmentPath) -> bool
	{
		glClearColor(58 / 255.f, 51 / 255.f, 51 / 255.f, 1.0f);

		if (shaderProgram != 0)
		{
			glDeleteProgram(shaderProgram);
			shaderProgram = 0;
		}

		std::string vertexShaderCode =
			file::file_loader::FileContent(vertexPath);

		std::string fragShaderCode =
			file::file_loader::FileContent(fragmentPath);

		const char* vertexShaderSource = vertexShaderCode.c_str();
		const char* fragShaderSource = fragShaderCode.c_str();

		//create shader object
		uint32_t vertexShader, fragmentShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Give shader objects their source code
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		int32_t status = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
		if (status == 0) {
			int32_t log_length;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &log_length);
			std::string log = std::string((std::size_t)log_length, ' ');
			glGetShaderInfoLog(vertexShader, log_length, nullptr, &log[0]);
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Vertex shader compile failed: %s", log.c_str());
			return false;
		}

		glShaderSource(fragmentShader, 1, &fragShaderSource, nullptr);
		glCompileShader(fragmentShader);

		status = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
		if (status == 0) {
			int32_t log_length;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &log_length);
			std::string log = std::string((std::size_t)log_length, ' ');
			glGetShaderInfoLog(fragmentShader, log_length, nullptr, &log[0]);
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Fragment shader compile failed: %s", log.c_str());
			return false;
		}

		//shader program creation -> opengl object
		shaderProgram = glCreateProgram();

		//attach shaders to the shader program 
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		//link shader program
		glLinkProgram(shaderProgram);

		status = 0;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
		if (status == 0) {
			int32_t log_length;
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &log_length);
			std::string log = std::string((std::size_t)log_length, ' ');
			glGetProgramInfoLog(shaderProgram, log_length, nullptr, &log[0]);
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Shader program linking failed failed: %s", log.c_str());
			return false;
		}

		glDeleteShader(vertexShader); //deallocation
		glDeleteShader(fragmentShader); //deallocation

		return true;
	}


	auto shader::Bind() noexcept -> void
	{
		//use shader program
		glUseProgram(shaderProgram);
	}

	auto shader::Unbind() noexcept -> void
	{
		glUseProgram(0);
		//glDeleteProgram(shaderProgram);

	}

	auto shader::Delete() noexcept -> void
	{
		if (shaderProgram != 0)
		{
			glDeleteProgram(shaderProgram);
			shaderProgram = 0;
		}
	}
}