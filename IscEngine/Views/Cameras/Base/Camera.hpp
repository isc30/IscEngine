#pragma once

#include <iostream>
using namespace std;

#include <GLM/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

namespace IscEngine {

	// Camera
	class Camera {

		protected:

		vec3 position;
		vec2 rotation;
		vec3 direction;

		mat4 view; // Camera view matrix

		// Updates current rotation of the camera based on direction
		void updateRotation();
		// Updates current direction of the camera based on rotation
		void updateDirection();
		// Updates camera view matrix based on position + direction
		void updateView();

		public:

		// Creates the Camera
		Camera();

		// Returns current position of the camera
		vec3 getPosition() const;
		// Sets a new position for the camera
		void setPosition(const vec3& position);

		// Returns current rotation of the camera
		vec2 getRotation() const;
		// Sets a new rotation for the camera
		void setRotation(const vec2& rotation);

		// Returns current direction of the camera
		vec3 getDirection() const;
		// Sets a new direction for the camera
		void setDirection(const vec3& direction);

		// Returns current view matrix of the camera
		mat4 getView() const;

		// Forces camera to look at a point
		void lookAt(const vec3& point);

	};

}