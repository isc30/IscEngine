#include "Camera.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////
// Default constructor
Camera::Camera() {

	this->position = vec3(0, 0, 0);
	this->direction = vec3(0, 0, -1); // Default OpenGL looks to -Z
	this->up = vec3(0, 1, 0);

	updateView();

}

//////////////////////////////////////////////////////////////////////
// Returns current position of the camera
vec3 Camera::getPosition() const {

	return this->position;

}

//////////////////////////////////////////////////////////////////////
// Sets a new position for the camera
void Camera::setPosition(const vec3& position){
	
	this->position = position;

	updateView();

}

//////////////////////////////////////////////////////////////////////
// Returns current direction of the camera
vec3 Camera::getDirection() const {

	return this->direction;

}

//////////////////////////////////////////////////////////////////////
// Sets a new direction for the camera
void Camera::setDirection(const vec3& direction) {

	this->direction = glm::normalize(direction);
	
	this->updateView();

}

//////////////////////////////////////////////////////////////////////
// Returns current up vector of the camera
vec3 Camera::getUp() const {

	return this->up;

}

//////////////////////////////////////////////////////////////////////
// Sets a new up vector for the camera
void Camera::setUp(const vec3& up) {

	this->up = up;

	updateView();

}

//////////////////////////////////////////////////////////////////////
// Returns current view matrix of the camera
mat4 Camera::getView() const {

	return this->view;

}


//////////////////////////////////////////////////////////////////////
// Forces camera to look at a point
void Camera::setTarget(const vec3& target) {
	
	this->direction = glm::normalize(target - this->position);
	
	this->updateView();

}

//////////////////////////////////////////////////////////////////////
// Updates camera view matrix based on position + direction
void Camera::updateView() {

	this->view = glm::lookAt(this->position, this->position + this->direction, this->up);

}