#pragma once

#include "Base/Scene.hpp"

namespace IscEngine { namespace Scenes {

	class TestScene : public Scene {

		private:

			uint fpsCount;
			sf::Time fpsTime;

		public:

			TestScene(Window* window);

			void processEvent(sf::Event event);

			void update();
			void processInput();
			void render();

	};

} }