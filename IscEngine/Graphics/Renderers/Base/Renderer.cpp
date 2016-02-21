#include "Renderer.hpp"
using namespace IscEngine;
using namespace IscEngine::Renderers;

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::clearEntities() {

	this->entities.clear();

}

void Renderer::addEntity(StaticEntity* const entity) {

	this->entities.push_back(entity);

}

void Renderer::addEntities(const vector<StaticEntity*>& entities) {

	this->entities.insert(this->entities.end(), entities.begin(), entities.end());

}

void Renderer::addEntities(const list<StaticEntity*>& entities) {

	this->entities.insert(this->entities.end(), entities.begin(), entities.end());

}

void Renderer::removeEntity(StaticEntity* const entity) {

	this->entities.remove(entity);

}

void Renderer::render(const mat4& P, const Camera* const camera) {

	mat4 VP = P * camera->getView();
	for (auto it = this->entities.begin(), end = this->entities.end(); it != end; ++it) {
		(*it)->render(1.f);
	}

}