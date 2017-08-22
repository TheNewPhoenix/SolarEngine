#pragma once

#include <string>
#include "..\Common.h"

namespace solar
{

	class SOLAR_API Shader
	{
	public:
		Shader(unsigned type);
		~Shader();

		bool setSource(const char* filepath);

		void compile();
		std::string getInfoLog();
		int getId() const { return m_id; };

	private:
		unsigned m_id;
		unsigned m_type;
	};

}