#pragma once

#include "../Engine.hpp"
#include "../Graphics/Shaders/Base/Shader.hpp"
#include "Base/Scene.hpp"

#include <GLM/gtx/vector_angle.hpp>

namespace IscEngine { namespace Scenes {

	class TestScene : public Scene {

		private:

			uint fpsCount;
			sf::Time fpsTime;
			Shader shader, shShadowMap;

		public:

			TestScene(Window* window);
			~TestScene();

			void processEvent(const sf::Event& event);

			void update();
			void processInput();
			void render();

	};

} }