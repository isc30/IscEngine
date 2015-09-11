#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <GLM/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

///////////////////////////////////////////////////////////////////////////////
// Gets a position, rotation and scale and returns a modelview matrix
mat4 getModelView(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 rotation = vec3(0.0f, 0.0f, 0.0f), vec3 scale = vec3(1.0f, 1.0f, 1.0f)){

	mat4 rotationMatrix(1.f);
	rotationMatrix = rotate(rotationMatrix, rotation.x, vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = rotate(rotationMatrix, rotation.y, vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = rotate(rotationMatrix, rotation.z, vec3(0.0f, 0.0f, 1.0f));

	return translate(position) * rotationMatrix * glm::scale(scale);

}

#endif