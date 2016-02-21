#pragma once

#include "Base\Renderer.hpp"
#include "../../Graphics/Shaders/Base/Shader.hpp"

namespace IscEngine { namespace Renderers {

	class Simple3D : public Renderer {

		private:

		Shader* shader;

		public:

		Simple3D();
		~Simple3D();

		void render(const mat4& P, const Camera* const camera);

	};

} }