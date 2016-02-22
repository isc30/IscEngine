#pragma once

#include "../Shaders/Base/Shader.hpp"

#include <glm/glm.hpp>
using namespace glm;

#include <string>

namespace IscEngine { namespace Graphics { namespace Lighting {

	class LightSource {

	public:

		vec3 position;
		vec3 color;
		float power;

		void setShaderUniforms(const Shader* const shader, const string& lightUniform) {

			shader->setUniform((lightUniform + ".position_worldspace").c_str(), this->position.x, this->position.y, this->position.z);
			shader->setUniform((lightUniform + ".color").c_str(), this->color.r, this->color.g, this->color.b);
			shader->setUniform((lightUniform + ".power").c_str(), this->power);

		}

	};

} } }