#include "Program.h"
#include "..\Graphics.h"
#include "..\Common.h"

#include <iostream>

namespace solar
{

	Program::Program()
	{
		m_id = glCreateProgram();
	}

	Program::~Program()
	{
		glDeleteProgram(m_id);
	}

	void Program::attach(Shader& shader)
	{
		glAttachShader(m_id, shader.getId());
	}

	void Program::link()
	{
		glLinkProgram(m_id);
	}

	void Program::use()
	{
		glUseProgram(m_id);
	}

	std::string Program::getInfoLog()
	{
		GLint maxLength = 0;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);
		std::string infoMessage = "Nothing to log";

		if (maxLength > 0)
		{
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_id, maxLength, &maxLength, &infoLog[0]);
			infoMessage = &infoLog[0];
		}

		return infoMessage;
	}

	unsigned Program::getAttributeLocation(const char* name)
	{
		use();

		if (m_attributeLocations.count(name))
			return m_attributeLocations[name];

		unsigned location = glGetAttribLocation(m_id, name);
		m_attributeLocations[name] = location;

		return location;
	}

	unsigned Program::getUniformLocation(const char* name)
	{
		use();

		if (m_uniformLocations.count(name))
			return m_uniformLocations[name];

		unsigned location = glGetUniformLocation(m_id, name);
		m_uniformLocations[name] = location;

		return location;
	}

	void Program::setUniform1f(const char* name, float value)
	{
		unsigned location = getUniformLocation(name);
		glUniform1f(location, value);
	}

	void Program::setUniformMatrix4fv(const char* name, glm::mat4& matrix, bool transpose)
	{
		unsigned location = getUniformLocation(name);
		glUniformMatrix4fv(location, 1, transpose, &matrix[0][0]);
	}

	void Program::setUniformVec3f(const char* name, float x, float y, float z) 
	{
		unsigned location = getUniformLocation(name);
		glUniform3f(location, x, y, z);
	}

	void Program::setUniformVec3fv(const char* name, glm::vec3& vertex)
	{
		unsigned location = getUniformLocation(name);
		glUniform3fv(location, 1, &vertex[0]);
	}

	void Program::setUniformColorRGB(const char* name, Color& color)
	{
		unsigned location = getUniformLocation(name);
		glUniform3f(location, color.m_r, color.m_g, color.m_b);
	}
}
