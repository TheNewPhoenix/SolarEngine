#include "Shader.h"
#include "..\Graphics.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace solar
{

	Shader::Shader(unsigned type) :
		m_type(type)
	{
		m_id = glCreateShader(type);
	}

	Shader::~Shader()
	{
		glDeleteShader(m_id);
	}

	bool Shader::setSource(const char* filepath)
	{
		std::ifstream inFile(filepath, std::ios::in);
		std::string source;
		std::stringstream stringStream;

		if (!inFile.is_open())
			perror(filepath);


		stringStream << inFile.rdbuf();
		source = stringStream.str();

		const char* sourcePointer = source.c_str();
		glShaderSource(m_id, 1, &sourcePointer, NULL);

		return true;
	}

	void Shader::compile()
	{
		glCompileShader(m_id);

		//TODO: handle exception if compile status is false
		GLint result;
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			SOLAR_LOGERROR("Unable to compile shader:\n" + getInfoLog());
		}

	}

	std::string Shader::getInfoLog()
	{
		GLint maxLength = 0;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);
		std::string infoMessage = "Nothing to log";

		if (maxLength > 0)
		{
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(m_id, maxLength, &maxLength, &infoLog[0]);
			infoMessage = &infoLog[0];

		}

		return infoMessage;
	}

}