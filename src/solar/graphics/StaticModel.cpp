#include "StaticModel.h"

namespace solar
{

	StaticModel::StaticModel()
	{
	}

	StaticModel::~StaticModel()
	{
	}

	void StaticModel::setModel(Model& model)
	{
		bool useDefualtMat = model.m_materials.size() == 0;
		for (unsigned i = 0; i < model.m_materials.size(); i++)
		{
			Material material;
			material.ambient = model.m_materials[i]->ambient;
			material.diffuse = model.m_materials[i]->diffuse;
			material.specular = model.m_materials[i]->specular;
			material.shininess = model.m_materials[i]->shininess;
			m_materials[model.m_materials[i]->id] = material;
		}

		for (unsigned i = 0; i < model.m_meshes.size(); i++)
		{
			ModelMesh* model_mesh = model.m_meshes[i].get();
			VertexAttributes attributes({});

			for (unsigned j = 0; j < model_mesh->attributes.size(); j++)
			{
				attributes.add(model_mesh->attributes[j]);
			}

			std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
			mesh->setAttributes(attributes);
			mesh->setVertices(model_mesh->vertices);
			mesh->setIndices(model_mesh->indices);
			if (useDefualtMat)
				mesh->setMaterial(Material::defaultMat());
			else
				mesh->setMaterial(m_materials[model_mesh->materialId]);
			m_meshes.push_back(mesh);
		}

	}

	void StaticModel::draw(Program* program)
	{
		for (unsigned i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i]->render(program, GL_TRIANGLES);
		}
	}

}