#pragma once

#include <iostream>
using namespace std;

#include <GLM/glm.hpp>
using namespace glm;

namespace IscEngine {

	// Camera
	class Camera {

		protected:

		vec3 position;
		vec3 direction;
		vec3 up;

		mat4 view; // Camera view matrix
		
		// Updates camera view matrix
		void updateView();

		public:

		// Creates the Camera
		Camera();

		// Returns current position of the camera
		vec3 getPosition() const;
		// Sets a new position for the camera
		void setPosition(const vec3& position);

		// Returns current direction of the camera
		vec3 getDirection() const;
		// Sets a new direction for the camera
		void setDirection(const vec3& direction);

		// Returns current up vector of the camera
		vec3 getUp() const;
		// Sets a new up vector for the camera
		void setUp(const vec3& up);

		// Forces camera to look at a point
		void setTarget(const vec3& target);

		// Returns current view matrix of the camera
		mat4 getView() const;

	};

}