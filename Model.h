#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
private:
	std::vector<Mesh*> meshList;
	std::vector<Texture*> textureList;
	std::vector<unsigned int> meshTotex;

	void LoadNode(aiNode* node,const aiScene* scene);
	void LoadMesh(aiMesh* mesh,const aiScene* scene);
	void LoadMaterials(const aiScene* scene);

public:
	Model();

	void LoadModel(const std::string& filename);
	void RenderModel();
	void ClearModel();

	~Model();
};

