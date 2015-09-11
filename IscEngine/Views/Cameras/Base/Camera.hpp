#pragma once

#include <iostream>
using namespace std;

#include <GLM/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

class Camera {

	protected:
		
		vec3 position;
		vec2 rotation;
		vec3 direction;

		mat4 view; // Camera view matrix for shader

		void updateRotation();
		void updateDirection();
		void updateView();

	public:
		
		Camera();

		vec3 getPosition();
		void setPosition(vec3 position);

		vec2 getRotation();
		void setRotation(vec2 rotation);

		vec3 getDirection();
		void setDirection(vec3 direction);

		mat4 getView();

		void lookAt(vec3 point);

};