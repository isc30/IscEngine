#pragma once

#include "../Graphics/Textures/Texture.hpp"
#include "../Graphics/Models/Mesh.hpp"

namespace IscEngine {

	class SkyBox {

		private:

			static Mesh* cube;
			static mat4 M;

		public:

			SkyBox() {};
			static void initializeStatic();
			void render();

	};

}