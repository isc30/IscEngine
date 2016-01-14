#pragma once

#include <iostream>
#include <queue>
using namespace std;

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GLM/glm.hpp>
using namespace glm;

#include "../../Graphics/Window.hpp"

namespace IscEngine {

	enum SceneEventType {

		SCENE_END

	};

	class SceneEvent {

		public:

			SceneEventType type;
			void* data;

	};

	class Scene {

		protected:

			Window* window;
			sf::Clock sceneClock;
			sf::Time deltaTime;

			queue<SceneEvent> sceneEventQueue;

		public:

			Scene(Window* window);
			virtual ~Scene();

			virtual void processEvent(const sf::Event& event) = 0;

			void pushEvent(const SceneEvent& sceneEvent);
			const bool pollEvent(SceneEvent& sceneEvent);

			void loop();
			virtual void update() = 0;
			virtual void render() = 0;

			virtual void endScene(Scene* scene);

	};

}