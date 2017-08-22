#pragma once
#include "..\Common.h"
#include "Color.h"
#include "opengl\VertexBuffer.h"
#include "opengl\VertexArray.h"
#include "opengl\Program.h"
#include "VertexAttributes.h"

#include <vector>

namespace solar
{

	struct Material
	{
		Color ambient;
		Color diffuse;
		Color specular;
		float shininess;

		static Material defaultMat()
		{
			Material material;
			material.ambient = Color(Color::GRAY)*0.1f;
			material.diffuse = Color(Color::GRAY)*0.7f;
			material.specular = Color(0.5f, 0.5f, 0.5f, 1.0f);
			material.shininess = 32.0f;
			return material;
		}
	};

	class SOLAR_API Mesh
	{
	public:
		Mesh();
		void setAttributes(VertexAttributes& attributes);
		void setAttributes(std::initializer_list<VertexAttribute> attributes);
		void setVertices(std::vector<float> vertices);
		void setIndices(std::vector<unsigned> indices);
		void setMaterial(Material& material);

		void bind(Program* program);
		void unbind(Program* program);
		void render(Program* program, unsigned primitiveType, int offset, int count);
		void render(Program* program, unsigned primitiveType);

	private:
		VertexBuffer m_vbo;
		VertexBuffer m_ibo;
		VertexArray m_vao;	
		VertexAttributes m_attributes;
		Material m_material;

		int m_numVertices;
		int m_numIndices;
	};
}