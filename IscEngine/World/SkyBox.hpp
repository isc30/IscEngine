#pragma once

#include "../Graphics/Textures/Texture.hpp"
#include "../Graphics/Models/Mesh.hpp"

namespace IscEngine {

	class SkyBox {

		private:

			static Mesh* cube;

		public:

			SkyBox() = delete;
			static void initializeStatic();
			static void render(const Texture* const front, const Texture* const back, const Texture* const right, const Texture* const left, const Texture* const up, const Texture* const down);

	};

}