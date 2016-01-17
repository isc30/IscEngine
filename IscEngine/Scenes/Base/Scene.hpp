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

	// Scene Event Types
	enum SceneEventType {

		SCENE_END

	};

	// Scene Event (type + data)
	class SceneEvent {

		public:

			SceneEventType type;
			void* data;

	};

	// Scene Base
	class Scene {

		protected:

			Window* window;
			sf::Clock sceneClock;
			sf::Time deltaTime;

			queue<SceneEvent> sceneEventQueue;

		public:
			
			// Creates the Scene
			Scene(Window* window);
			// Destructs the Scene
			virtual ~Scene() {};

			// Process the Window Event
			virtual void processEvent(const sf::Event& event) = 0;

			// Push new Scene Event
			void pushEvent(const SceneEvent& sceneEvent);
			// Polls the first Scene Event
			bool pollEvent(SceneEvent& sceneEvent);

			// Updates and Renders the scene while calculating deltaTime
			void loop();
			// Updates the Scene
			virtual void update() = 0;
			// Renders the Scene
			virtual void render() = 0;

			// Ends the Scene
			virtual void endScene(Scene* scene = nullptr);

	};

}