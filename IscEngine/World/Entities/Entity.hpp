#pragma once

#include <GLM/glm.hpp>
using namespace glm;

#include "../../Views/ModelView.hpp"

namespace IscEngine {

	class Entity {

		protected:

			vec3 position;
			vec3 rotation;
			vec3 scale;

			mat4 modelMatrix;

			void updateModelMatrix(); // Fails

		public:
			
			Entity();

			vec3 getPosition() const;	
			void setPosition(const vec3& position);

			vec3 getRotation() const;
			void setRotation(const vec3& rotation);

			vec3 getScale() const;
			void setScale(const vec3& scale);

			mat4 getModelMatrix() const;

	};

}