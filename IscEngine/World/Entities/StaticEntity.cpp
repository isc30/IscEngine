#include "StaticEntity.hpp"
using namespace IscEngine;

StaticEntity::StaticEntity(Mesh* const mesh) : Entity() {

	this->meshes[0.f] = mesh;

}

void StaticEntity::addMesh(const float distance, Mesh* const mesh) {

	this->meshes[distance] = mesh;

}

void StaticEntity::render(const float distance) {
	
	Mesh* renderMesh = this->meshes.begin()->second;
	for (auto it = this->meshes.begin(), end = this->meshes.end(); it != end; ++it) {
		if (distance >= (*it).first) {
			renderMesh = (*it).second;
		}
	}

	renderMesh->render(GL_TRIANGLES);

}