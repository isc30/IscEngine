#pragma once

#include "../Engine.hpp"

#include "Base/Scene.hpp"
#include "../Utils/Log.hpp"
#include "../Graphics/Shaders/Base/Shader.hpp"
#include "../Graphics/Models/Mesh.hpp"

namespace IscEngine { namespace Scenes {

	class TestScene : public Scene {

		private:

			uint fpsCount;
			sf::Time fpsTime;
			Shader shader, shShadowMap;
			Mesh* mesh[2];

		public:

			TestScene(Window* window);
			~TestScene();

			void processEvent(const sf::Event& event);

			void update();
			void processInput();
			void render();

	};

} }