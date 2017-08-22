#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>

#include "Shader.h"
#include "..\Color.h"

namespace solar
{

	class SOLAR_API Program
	{
	public:
		Program();
		~Program();

		void attach(Shader& shader);
		void link();
		void use();

		std::string getInfoLog();
		unsigned getAttributeLocation(const char* name);
		unsigned getUniformLocation(const char* name);

		void setUniform1f(const char* name, float value);
		void setUniformMatrix4fv(const char* name, glm::mat4& matrix, bool transpose = false);
		void setUniformVec3f(const char* name, float x, float y, float z);
		void setUniformVec3fv(const char* name, glm::vec3& vertex);
		void setUniformColorRGB(const char* name, Color& color);

	private:
		unsigned m_id;
		std::map<std::string, int> m_uniformLocations;
		std::map<std::string, int> m_attributeLocations;
	};

}