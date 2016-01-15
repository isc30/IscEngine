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

		const vec3 getPosition() const;
		void setPosition(const vec3 position);

		const vec2 getRotation() const;
		void setRotation(const vec2 rotation);

		const vec3 getDirection() const;
		void setDirection(const vec3 direction);

		const mat4 getView() const;

		void lookAt(const vec3 point);

};