#include "Entity.hpp"
using namespace IscEngine;

#include <iostream>

Entity::Entity() {

	this->position = vec3(0.f, 0.f, 0.f);
	this->rotation = vec3(0.f, 0.f, 0.f);
	this->scale = vec3(1.f, 1.f, 1.f);

	this->updateModelMatrix();

}

Entity::~Entity() {



}

void Entity::updateModelMatrix() {

	this->modelMatrix = ModelView::getModelView(this->position, this->rotation, this->scale);

}

vec3 Entity::getPosition() const {

	return this->position;

}

void Entity::setPosition(const vec3& position) {
	
	if (this->position != position) {

		this->position = position;
		this->updateModelMatrix();

	}

}

vec3 Entity::getRotation() const {

	return this->rotation;

}

void Entity::setRotation(const vec3& rotation) {

	if (this->rotation != rotation) {

		this->rotation = rotation;

		float max = radians(360.f);
		while (this->rotation.x >= max) this->rotation.x -= max;
		while (this->rotation.y >= max) this->rotation.y -= max;
		while (this->rotation.z >= max) this->rotation.z -= max;

		this->updateModelMatrix();

	}

}

vec3 Entity::getScale() const {

	return this->scale;

}

void Entity::setScale(const vec3& scale) {

	if (this->scale != scale) {

		this->scale = scale;
		this->updateModelMatrix();

	}

}

const mat4 Entity::getModelMatrix() const {

	return this->modelMatrix;

}