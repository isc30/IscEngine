#include "objloader.hpp"
#include "../../../Utils/Log.hpp"
using namespace IscEngine;

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool loadModel(
	string path,
	std::vector<unsigned int> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals
) {

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);
	if (!scene) {
		fprintf(stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	
	unsigned int offset = 0;
	for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++) {
		
		const aiMesh* mesh = scene->mMeshes[meshIndex];

		//vertices.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D pos = mesh->mVertices[i];
			vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
		}

		// Fill vertices texture coordinates
		//uvs.reserve(mesh->mNumVertices);
		if (mesh->HasTextureCoords(0))
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
			uvs.push_back(glm::vec2(UVW.x, UVW.y));
		}

		// Fill vertices normals
		//normals.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			if (mesh->HasNormals()) {
				aiVector3D n = mesh->mNormals[i];
				normals.push_back(glm::vec3(n.x, n.y, n.z));
			} else {
				normals.push_back(glm::vec3(1, 1, 1));
			}
		}
		
		// Fill face indices
		//indices.reserve(3 * mesh->mNumFaces);
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			// Assume the model has only triangles.
			indices.push_back(mesh->mFaces[i].mIndices[0] + offset);
			indices.push_back(mesh->mFaces[i].mIndices[1] + offset);
			indices.push_back(mesh->mFaces[i].mIndices[2] + offset);
		}

		offset += mesh->mNumVertices;

	}


	// The "scene" pointer will be deleted automatically by "importer"

	return true;

}