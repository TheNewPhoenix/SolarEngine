#include "Mesh.h"
#include "Graphics.h"

namespace solar
{

	Mesh::Mesh() :
		m_vao(),
		m_vbo(GL_ARRAY_BUFFER),
		m_ibo(GL_ELEMENT_ARRAY_BUFFER),
		m_attributes({}),
		m_material(Material::defaultMat()),
		m_numVertices(0),
		m_numIndices(0)
	{
		m_vao.bind();
		m_vbo.bind();
		m_ibo.bind();
	}

	void Mesh::setAttributes(VertexAttributes& attributes)
	{
		m_attributes = attributes;
	}

	void Mesh::setAttributes(std::initializer_list<VertexAttribute> attributes)
	{
		VertexAttributes vAttributes(attributes);
		setAttributes(vAttributes);
	}

	void Mesh::setVertices(std::vector<float> vertices)
	{
		m_numVertices = vertices.size();
		m_vbo.bind();
		m_vbo.setData(vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	}

	void Mesh::setIndices(std::vector<unsigned> indices)
	{
		m_numIndices = indices.size();
		m_ibo.bind();
		m_ibo.setData(indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
	}

	void Mesh::setMaterial(Material& material)
	{
		m_material = material;
	}

	void Mesh::bind(Program* program)
	{
		program->use();
	
		program->setUniformColorRGB("u_material.ambient", m_material.ambient);
		program->setUniformColorRGB("u_material.diffuse", m_material.diffuse);
		program->setUniformColorRGB("u_material.specular", m_material.specular);
		program->setUniform1f("u_material.shininess", m_material.shininess);

		int numAttributes = m_attributes.size();

		m_vbo.bind();
		for (int i = 0; i < numAttributes; i++) 
		{
			VertexAttribute* attribute = m_attributes.get(i);
			int location = program->getAttributeLocation(attribute->name);

			m_vao.enableAttributeArray(location);
			m_vao.pointAttribute(location, attribute->numComponents, attribute->type, attribute->normalized, m_attributes.vertexSize, attribute->offset);
		}
	}

	void Mesh::unbind(Program* program)
	{
		int numAttributes = m_attributes.size();

		for (int i = 0; i < numAttributes; i++)
		{
			VertexAttribute* attribute = m_attributes.get(i);
			int location = program->getAttributeLocation(attribute->name);

			m_vao.disableAttributeArray(location);
		}
	}

	void Mesh::render(Program* program, unsigned primitiveType, int offset, int count)
	{
		bind(program);

		if (m_numIndices > 0)
		{
			m_ibo.bind();
			glDrawElements(primitiveType, count, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(primitiveType, offset, count);
		}
		unbind(program);
	}

	void Mesh::render(Program* program, unsigned primitiveType)
	{
		render(program, primitiveType, 0, m_numIndices);
	}

}