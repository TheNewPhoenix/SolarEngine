#include "VertexAttributes.h"

namespace solar
{
	VertexAttributes::VertexAttributes(std::initializer_list<VertexAttribute> attributes) :
		m_attributes(attributes)
	{
		vertexSize = calcOffsets();
	}

	unsigned VertexAttributes::getOffset(Usage& usage)
	{
		VertexAttribute* attribute = findByUsage(usage);
		return attribute->offset;
	}

	VertexAttribute* VertexAttributes::findByUsage(Usage& usage)
	{
		int length = size();
		for (int i = 0; i < length; i++)
			if (get(i)->usage == usage) return get(i);
		return 0;
	}

	int VertexAttributes::size()
	{
		return m_attributes.size();
	}

	VertexAttribute* VertexAttributes::get(int i)
	{
		return &m_attributes[i];
	}

	void VertexAttributes::add(VertexAttribute& attribute)
	{
		m_attributes.push_back(attribute);
		vertexSize = calcOffsets();
	}

	int VertexAttributes::calcOffsets()
	{
		int count = 0;
		for (unsigned i = 0; i < m_attributes.size(); i++)
		{
			VertexAttribute& attribute = m_attributes[i];
			attribute.offset = count;
			count += attribute.getSizeInBytes();
		}

		return count;
	}

}