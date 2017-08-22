#pragma once

#include <string>
#include "Graphics.h"

#include <initializer_list>

namespace solar
{

	enum Usage
	{
		POSITION,
		COLOR,
		NORMAL,
		TEXCOORDS
	};

	struct SOLAR_API VertexAttribute
	{
		Usage usage;
		int numComponents;
		int type;
		bool normalized;
		int offset;
		const char* name;

		VertexAttribute(Usage usage, int numComponents, int type, bool normalized, const char* name) :
			usage(usage),
			numComponents(numComponents),
			type(type),
			normalized(normalized),
			name(name)
		{
		}

		static VertexAttribute Position()
		{
			return VertexAttribute(Usage::POSITION, 3, GL_FLOAT, false, "a_position");
		}

		static VertexAttribute Color()
		{
			return VertexAttribute(Usage::COLOR, 4, GL_FLOAT, false, "a_color");
		}

		static VertexAttribute TextCoord()
		{
			return VertexAttribute(Usage::TEXCOORDS, 2, GL_FLOAT, false, "a_texCoord0");
		}

		static VertexAttribute Normal()
		{
			return VertexAttribute(Usage::NORMAL, 3, GL_FLOAT, false, "a_normal");
		}

		int getSizeInBytes()
		{
			switch (type)
			{
			case GL_FLOAT:
				return 4 * numComponents;
			case GL_BYTE:
				return numComponents;
			case GL_SHORT:
				return 2 * numComponents;
			}
			return 0;
		}

	};

	class SOLAR_API VertexAttributes
	{
	public:
		VertexAttributes(std::initializer_list<VertexAttribute> attributes);
		unsigned getOffset(Usage& usage);
		VertexAttribute* findByUsage(Usage& usage);
		int size();
		VertexAttribute* get(int i);
		void add(VertexAttribute& attribute);
		
		unsigned vertexSize;

	private:
		std::vector<VertexAttribute> m_attributes;
		int calcOffsets();
	};

}