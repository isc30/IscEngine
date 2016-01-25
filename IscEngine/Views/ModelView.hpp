#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

namespace IscEngine { 
	
	class ModelView {
	
		public:

			ModelView() = delete;

			///////////////////////////////////////////////////////////////////////////////
			// Gets a position, rotation and scale and returns a modelview matrix
			static const mat4 getModelView(const vec3& position = vec3(0.0f, 0.0f, 0.0f), const vec3& rotation = vec3(0.0f, 0.0f, 0.0f), const vec3& scale = vec3(1.0f, 1.0f, 1.0f)) {

				mat4 rotationMatrix(1.f);
				rotationMatrix = rotate(rotationMatrix, rotation.x, vec3(1.0f, 0.0f, 0.0f));
				rotationMatrix = rotate(rotationMatrix, rotation.y, vec3(0.0f, 1.0f, 0.0f));
				rotationMatrix = rotate(rotationMatrix, rotation.z, vec3(0.0f, 0.0f, 1.0f));

				return translate(position) * rotationMatrix * glm::scale(scale);

			}
	
	};

}