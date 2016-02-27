#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include "../Textures/Texture.hpp"

namespace IscEngine { namespace Graphics { namespace Materials {

	struct MaterialProperties {

		float shininess = 10.f;
		vec3 specularColor = vec3(1, 1, 1);

	};

	struct Material {

		Texture* diffuseMap = nullptr;
		Texture* specularMap = nullptr;
		Texture* normalMap = nullptr;
		MaterialProperties materialProperties;

	};

} } }