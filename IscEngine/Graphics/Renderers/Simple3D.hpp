#pragma once

#include "Base\Renderer.hpp"
#include "../../Graphics/Shaders/Base/Shader.hpp"
#include "../Lighting/LightSetup.hpp"
using namespace IscEngine::Graphics::Lighting;

namespace IscEngine { namespace Renderers {

	class Simple3D : public Renderer {

		private:

		Shader* shader;
		LightSetup lightSetup;

		public:

		Simple3D();
		~Simple3D();

		void render(const mat4& P, const Camera* const camera);

		void addLightSource(LightSource* const light);
		void addLightSource(const vector<LightSource*>& light);
		void addLightSource(const list<LightSource*>& light);
		void removeLightSource(LightSource* const light);
		void clearLightSource();

	};

} }