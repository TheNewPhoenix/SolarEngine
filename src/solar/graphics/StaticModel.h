#pragma once

#include "Mesh.h"
#include "opengl\Program.h"
#include "..\resource\Model.h"

namespace solar
{

	class StaticModel
	{
	public:
		StaticModel();
		~StaticModel();

		void setModel(Model& model);

		void draw(Program* program);

	private:
		Mesh* mesh;
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		std::map<std::string, Material> m_materials;
		std::shared_ptr<Model> m_model;
	};

}