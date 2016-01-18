#pragma once

#include "Base/Shader.hpp"
#include "../Textures/Texture.hpp"
#include "../Models/Mesh.hpp"

namespace IscEngine {

	class PostProcess {

		private:

			static Mesh* quad;

		public:
			
			static void render(Texture* const texture);

	};

}