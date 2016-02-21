#pragma once

#include <glm/glm.hpp>
using namespace glm;

namespace IscEngine { namespace Graphics { namespace Lighting {

	struct LightSource {

		vec3 position;
		vec3 color;
		float power;

	};

} } }