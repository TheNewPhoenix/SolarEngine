#pragma once
#include "..\Common.h"

namespace solar
{
	class SOLAR_API VertexBuffer
	{
	public:
		VertexBuffer(int target);

		~VertexBuffer();

		void setData(unsigned size, const void* data, int usage);

		void resize(unsigned size, int usage);

		void setSubData(unsigned offset, unsigned size, const void* data);

		void bind();

		void unbind();

		unsigned getId() const { return m_id; }
	private:
		unsigned m_id;
		
		unsigned m_size;

		int m_target;

	};

}