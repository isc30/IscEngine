#include "Camera.hpp"

//////////////////////////////////////////////////////////////////////
// Default constructor
Camera::Camera() {

	this->position = vec3(0, 0, 0);
	this->rotation = vec2(0, 0);
	this->direction = vec3(0, 0, 1); // Default OpenGL looks to -Z

	updateView();

}

//////////////////////////////////////////////////////////////////////
// Returns current position of the camera
const vec3 Camera::getPosition() const {

	return this->position;

}

//////////////////////////////////////////////////////////////////////
// Sets a new position for the camera
void Camera::setPosition(const vec3 position){
	
	this->position = position;

	updateView();

}

//////////////////////////////////////////////////////////////////////
// Returns current rotation of the camera
const vec2 Camera::getRotation() const {
	
	return this->rotation;

}

//////////////////////////////////////////////////////////////////////
// Sets a new rotation for the camera
void Camera::setRotation(const vec2 rotation){
	
	this->rotation = rotation;

	updateDirection();
	updateView();

}

//////////////////////////////////////////////////////////////////////
// Returns current direction of the camera
const vec3 Camera::getDirection() const {

	return this->direction;

}

//////////////////////////////////////////////////////////////////////
// Returns current direction of the camera
void Camera::setDirection(const vec3 direction) {

	this->direction = direction;

	this->updateRotation();
	this->updateView();

}

//////////////////////////////////////////////////////////////////////
// Returns current view matrix of the camera
const mat4 Camera::getView() const {

	return this->view;

}


//////////////////////////////////////////////////////////////////////
// Forces camera to look at a point
void Camera::lookAt(const vec3 point) {

	this->view = glm::lookAt(this->position, point, vec3(0, 1, 0));
	this->direction = glm::normalize(point - this->position);

	this->updateRotation();
	this->updateView();

}

//////////////////////////////////////////////////////////////////////
// Updates current rotation of the camera based on direction
void Camera::updateRotation() {

	float distXZ = sqrt(this->direction.x * this->direction.x + this->direction.z * this->direction.z);
	float distXYZ = sqrt(this->direction.x * this->direction.x + this->direction.y * this->direction.y + this->direction.z * this->direction.z);

	if (this->direction.x != 0 || this->direction.z != 0) {
		this->rotation.y = degrees(acos(this->direction.z / distXZ));
	}

	if (this->direction.x != 0 || this->direction.y != 0 || this->direction.z != 0) {
		this->rotation.x = -degrees(acos(distXZ / distXYZ));
	}

	if (this->direction.x > 0) {
		this->rotation.y = -this->rotation.y;
	}

	if (this->direction.y > 0) {
		this->rotation.x = -this->rotation.x;
	}

}

//////////////////////////////////////////////////////////////////////
// Updates current direction of the camera
void Camera::updateDirection() {

	if (this->rotation.y > 360) this->rotation.y -= 360;
	if (this->rotation.y < 0) this->rotation.y += 360;
	if (this->rotation.x > 89) this->rotation.x = 89;
	if (this->rotation.x < -89) this->rotation.x = -89;

	float sinX = sin(radians(this->rotation.x));
	float cosX = cos(radians(this->rotation.x));
	float sinY = sin(radians(this->rotation.y));
	float cosY = cos(radians(this->rotation.y));

	this->direction = vec3(cosX * sinY,	sinX, cosX * cosY);

}

//////////////////////////////////////////////////////////////////////
// Updates camera view matrix
void Camera::updateView() {

	this->view = glm::lookAt(this->position, this->position + this->direction, vec3(0, 1, 0));

}