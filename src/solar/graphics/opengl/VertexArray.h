#pragma once

#include "VertexBuffer.h"

namespace solar
{

	class SOLAR_API VertexArray
	{
	public:
		VertexArray();

		~VertexArray();

		void bind();

		void unbind();

		void enableAttributeArray(int index);

		void disableAttributeArray(int index);

		void pointAttribute(unsigned index, unsigned count, unsigned type, bool normalized = false, unsigned stride = 0, unsigned offset = 0);
		
	private:
		unsigned m_id;
	};

}