#include "VertexArray.h"
#include "..\Graphics.h"

#include <iostream>

namespace solar
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::enableAttributeArray(int index)
	{
		glEnableVertexAttribArray(index);
	}

	void VertexArray::disableAttributeArray(int index)
	{
		glDisableVertexAttribArray(index);
	}

	void VertexArray::pointAttribute(unsigned index, unsigned count, unsigned type, bool normalized, unsigned stride, unsigned offset)
	{
		bind();
		glVertexAttribPointer(index, count, type, normalized, stride, (const void*)(size_t)offset);
	}
}