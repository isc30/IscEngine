#include "StaticEntity.hpp"
using namespace IscEngine;

StaticEntity::StaticEntity(Mesh* const mesh) : Entity() {

	this->meshes[0.f] = mesh;

}

void StaticEntity::addMesh(const float distance, Mesh* const mesh) {

	this->meshes[distance] = mesh;

}

void StaticEntity::render(mat4& VP) {

	vec4 model_cameraspace = VP * this->getModelMatrix() * vec4(0, 4, 0, 1);

	if (model_cameraspace.z >= 0.f && model_cameraspace.z <= 1000.0f &&
		model_cameraspace.x / model_cameraspace.w >= -1.f && model_cameraspace.x / model_cameraspace.w <= 1.f &&
		model_cameraspace.y / model_cameraspace.w >= -1.f && model_cameraspace.y / model_cameraspace.w <= 1.f) {

		Shader::currentShader->setUniformMatrix("M", &this->getModelMatrix()[0][0]);

		Mesh* renderMesh = this->meshes.begin()->second;
		for (auto it = this->meshes.begin(), end = this->meshes.end(); it != end; ++it) {
			if (model_cameraspace.z >= (*it).first) {
				renderMesh = (*it).second;
			}
		}

		renderMesh->render(GL_TRIANGLES);

	}

}