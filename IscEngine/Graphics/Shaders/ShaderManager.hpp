#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GLM/glm.hpp>
using namespace glm;

#include "Base/Shader.hpp"

namespace IscEngine {

	class ShaderManager {

		public:
			static Shader* currentShader;

	};

}