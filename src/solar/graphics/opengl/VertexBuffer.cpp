#include "VertexBuffer.h"
#include "..\Graphics.h"

namespace solar
{

	VertexBuffer::VertexBuffer(int target) :
		m_target(target),
		m_size(0)
	{
		glGenBuffers(1, &m_id);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexBuffer::setData(unsigned size, const void* data, int usage)
	{
		bind();
		m_size = sizeof(data);	
		glBufferData(m_target, size, data, usage);
	}

	void VertexBuffer::resize(unsigned size, int usage)
	{
		bind();
		m_size = size;
		glBufferData(m_target, size, NULL, usage);
	}

	void VertexBuffer::setSubData(unsigned offset, unsigned size, const void* data)
	{

	}

	void VertexBuffer::bind()
	{
		glBindBuffer(m_target, m_id);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(m_target, 0);
	}

}