/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:20:53 by capi              #+#    #+#             */
/*   Updated: 2026/01/12 17:54:47 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GL_Wrapper/Shader.hpp"

using namespace GL_Wrapper;

Shader::Shader(const char *vs_file_name, const char *fs_file_name)
{
	unsigned int vertex_shader = 0;
	unsigned int fragment_shader = 0;
	try
	{
		vertex_shader = this->createShader(vs_file_name, GL_VERTEX_SHADER);
		fragment_shader = this->createShader(fs_file_name, GL_FRAGMENT_SHADER);

		this->_id = glCreateProgram();
		if (!this->_id)
		{
			GLLogCall("GLShaderProgram", __FILE__, __LINE__);
			std::string error_msg = "Error: Failed to create shader program";
			throw std::runtime_error(error_msg);
		}

		GLCallThrow(glAttachShader(this->_id, vertex_shader));
		GLCallThrow(glAttachShader(this->_id, fragment_shader));

		glLinkProgram(this->_id);
		int success;
		char infoLog[512];
		glGetProgramiv(this->_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->_id, 512, NULL, infoLog);
			std::string error_msg = "Error: Failed to link shaders to the shader_programm: " + std::string(infoLog);
			throw std::runtime_error(error_msg);
		}
	}
	catch(const std::exception& e)
	{
		if (vertex_shader >= 0)
			glDeleteShader(vertex_shader);
		if (fragment_shader >= 0)
			glDeleteShader(fragment_shader);
		if (this->_id > 0)
			glDeleteProgram(this->_id);
		throw;
	}
}

Shader::~Shader(void)
{
	glDeleteProgram(this->_id);
}

unsigned int	Shader::createShader(const char *file_name, GLenum shader_type)
{
	unsigned int shader_id = 0;
	try
	{
		shader_id = glCreateShader(shader_type);
		if (!shader_id)
		{
			GLLogCall("createShader", __FILE__, __LINE__);
			throw std::runtime_error("Error: Failed to create shader");
		}
		
		std::ifstream file(file_name);
		if (!file.is_open())
		{
			std::string error_msg = "Cannot open shader file : " + std::string(file_name);
			throw std::runtime_error(error_msg);
		}

		std::string line;
		std::string source;
		while (std::getline(file, line))
		{
			source += line;
			source += "\n";
		}
		file.close();

		const char *source_c = source.c_str();
		GLCallThrow(glShaderSource(shader_id, 1, &source_c, NULL));

		glCompileShader(shader_id);
		int success;
		char infoLog[512];
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
			std::string error_msg = "Error: Failed to compile shader: " + std::string(infoLog);
			throw std::runtime_error(error_msg);
		}
	}
	catch(const std::exception& e)
	{
		if (shader_id > 0)
			glDeleteShader(shader_id);
		throw;
	}
	return (shader_id);
}

void	Shader::use(void) const
{
	glUseProgram(this->_id);
}

void	Shader::setBool(const std::string &name, bool value) const
{
	int location = glGetUniformLocation(this->_id, name.c_str());
	glUniform1i(location, (int)value);
}

void	Shader::setInt(const std::string &name, int value) const
{
	int location = glGetUniformLocation(this->_id, name.c_str());
	glUniform1i(location, value);
}

void	Shader::setFloat(const std::string &name, float value) const
{
	int location = glGetUniformLocation(this->_id, name.c_str());
	glUniform1f(location, value);
}


void	Shader::setMat4(const std::string &name, glm::mat4 mat) const
{
	int location = glGetUniformLocation(this->_id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}