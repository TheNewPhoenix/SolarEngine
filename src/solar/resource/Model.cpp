#include "Model.h"

namespace solar
{

	Model::Model()
	{
	}

	Model::~Model()
	{
	}

	void Model::load(const char* filepath)
	{
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(filepath, 
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			SOLAR_LOGERROR() << "ERROR::ASSIMP::" << importer.GetErrorString();
			return;
		}

		processScene(scene);
	}

	void Model::processScene(const aiScene* scene)
	{
		SOLAR_LOGDEBUG() << "Processing scene";

		for (unsigned i = 0; i < scene->mNumMaterials; i++)
			processMaterial(scene->mMaterials[i], scene);

		processNode(scene->mRootNode, scene);

	}

	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		SOLAR_LOGDEBUG() << "Processing node: " << node->mName.C_Str();
		for (unsigned i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, scene);
		}

		for (unsigned i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	void Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		SOLAR_LOGDEBUG() << "Processing mesh: " << mesh->mName.C_Str();
		std::shared_ptr<ModelMesh> model_mesh = std::make_shared<ModelMesh>();

		model_mesh->id = mesh->mName.C_Str();

		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			model_mesh->id = mesh->mName.C_Str();

			float x = mesh->mVertices[i].x;
			float y = mesh->mVertices[i].y;
			float z = mesh->mVertices[i].z;
			model_mesh->vertices.insert(model_mesh->vertices.end(), { x, y, z });

			if (mesh->HasNormals())
			{
				float nx = mesh->mNormals[i].x;
				float ny = mesh->mNormals[i].y;
				float nz = mesh->mNormals[i].z;
				model_mesh->vertices.insert(model_mesh->vertices.end(), { nx, ny, nz });
			}

			if (mesh->HasTextureCoords(0))
			{
				float u = mesh->mTextureCoords[0][i].x;
				float v = mesh->mTextureCoords[0][i].y;
				model_mesh->vertices.insert(model_mesh->vertices.end(), { u, v });
			}
		}

		for (unsigned i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				model_mesh->indices.push_back(face.mIndices[j]);
			}
		}

		model_mesh->attributes.push_back(VertexAttribute::Position());
		if (mesh->HasNormals())
			model_mesh->attributes.push_back(VertexAttribute::Normal());
		if (mesh->HasTextureCoords(0))
			model_mesh->attributes.push_back(VertexAttribute::TextCoord());

		if (m_materials.size() > 0) 
		{
			model_mesh->materialId = m_materials[mesh->mMaterialIndex]->id;
		}

		m_meshes.push_back(model_mesh);
	}

	void Model::processMaterial(aiMaterial* material, const aiScene* scene)
	{

		std::shared_ptr<ModelMaterial> model_material = std::make_shared<ModelMaterial>();

		aiString mname;
		material->Get(AI_MATKEY_NAME, mname);
		if (mname.length > 0)
			model_material->id = mname.C_Str();

		aiColor3D dif(0.f, 0.f, 0.f);
		aiColor3D amb(0.f, 0.f, 0.f);
		aiColor3D spec(0.f, 0.f, 0.f);
		float shine = 0.0;

		material->Get(AI_MATKEY_COLOR_AMBIENT, amb);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, dif);
		material->Get(AI_MATKEY_COLOR_SPECULAR, spec);
		material->Get(AI_MATKEY_SHININESS, shine);

		model_material->ambient = Color(amb.r, amb.g, amb.b) * 0.2f;
		model_material->diffuse = Color(dif.r, dif.g, dif.b);
		model_material->specular = Color(spec.r, spec.g, spec.b);
		model_material->shininess = shine;

		if (model_material->shininess == 0)
			model_material->shininess = 32.0f;

		m_materials.push_back(model_material);
	}

}