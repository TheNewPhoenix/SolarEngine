#pragma once

#include "..\graphics\VertexAttributes.h"
#include "..\graphics\Color.h"

#include <glm\glm.hpp>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

namespace solar
{

	struct ModelTexture
	{
		const static int USAGE_UNKNOWN = 0;
		const static int USAGE_NONE = 1;
		const static int USAGE_DIFFUSE = 2;
		const static int USAGE_EMISSIVE = 3;
		const static int USAGE_AMBIENT = 4;
		const static int USAGE_SPECULAR = 5;
		const static int USAGE_SHININESS = 6;
		const static int USAGE_NORMAL = 7;
		const static int USAGE_BUMP = 8;
		const static int USAGE_TRANSPARENCY = 9;
		const static int USAGE_REFLECTION = 10;

		std::string id;
		std::string fileName;
		glm::vec2 uvTranslation;
		glm::vec2 uvScaling;
		int usage;
	};

	struct ModelMaterial
	{
		std::string id;

		Color ambient;
		Color diffuse;
		Color specular;

		float shininess;
		float opacity = 1.0f;

		std::vector<ModelTexture> textures;
	};

	struct ModelMesh
	{
		std::string id;
		std::vector<VertexAttribute> attributes;
		std::vector<float> vertices;
		std::vector<unsigned> indices;
		std::string materialId;
	};
	

	class Model
	{
	public:
		Model();

		~Model();

		void load(const char* filepath);
		
		std::vector<std::shared_ptr<ModelMesh>> m_meshes;
		std::vector<std::shared_ptr<ModelMaterial>> m_materials;

	private:
		void processScene(const aiScene* scene);
		void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
		void processMaterial(aiMaterial* material, const aiScene* scene);
	};
}