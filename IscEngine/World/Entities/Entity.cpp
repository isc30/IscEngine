#include "Entity.hpp"
using namespace IscEngine;

#include <iostream>

Entity::Entity() {

	this->position = vec3(0, 0, 0);
	this->rotation = vec3(0, 0, 0);
	this->scale = vec3(0, 0, 0);

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

mat4 Entity::getModelMatrix() const {

	return this->modelMatrix;

}