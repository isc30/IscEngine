#include "StaticEntity.hpp"
using namespace IscEngine;

StaticEntity::StaticEntity() : Entity() {

	this->mesh = nullptr;
	this->lowPolyMesh = nullptr;

	this->lodDistance = 10;

}

void StaticEntity::setMesh(Mesh* const mesh) {

	this->mesh = mesh;

}

void StaticEntity::setLowPolyMesh(Mesh* const lowPolyMesh) {

	this->lowPolyMesh = lowPolyMesh;

}

void StaticEntity::setLodDistance(const float lodDistance) {

	this->lodDistance = lodDistance;

}

void StaticEntity::render(mat4& VP) {

	vec4 model_cameraspace = VP * this->modelMatrix * vec4(0, 0, 0, 1);
	if (model_cameraspace.z >= 0.f && model_cameraspace.z <= 1000.0f &&
		model_cameraspace.x / model_cameraspace.w >= -1.f && model_cameraspace.x / model_cameraspace.w <= 1.f &&
		model_cameraspace.y / model_cameraspace.w >= -1.f && model_cameraspace.y / model_cameraspace.w <= 1.f) {

		Shader::currentShader->setUniformMatrix("M", &this->getModelMatrix()[0][0]);

		if (model_cameraspace.z > this->lodDistance && this->lowPolyMesh != nullptr) {

			this->lowPolyMesh->render(GL_TRIANGLES);

		} else {

			this->mesh->render(GL_TRIANGLES);

		}

	}

}