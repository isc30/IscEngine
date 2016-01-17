#pragma once

#include <iostream>
#include <fstream>
using namespace std;

static const string RESOURCE_PATH = "../IscEngine/IscEngine/Resources/"; // ../IscEngine/IscEngine/Resources/

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <GLM/glm.hpp>
using namespace glm;

#include "Graphics/Window.hpp"
#include "Scenes/Base/Scene.hpp"

namespace IscEngine {

	// IscEngine Base
	class Engine {

		private:

			Window* window;
			Scene* currentScene;
			
			// GameLoop
			void loop();
			// Setups OpenGL (glew, ...)
			void setupOpenGL();

		public:
			
			// Creates the Engine
			Engine();
			// Destroys the Engine
			~Engine();

			// Returns the Window
			Window* getWindow() const;
			
			// Creates a Window
			void create(const string& title, const unsigned int width, const unsigned int height, const unsigned int style);
			// Runs the GameLoop
			void run();

			// Changes the current Scene
			void setScene(Scene* const scene);

	};

}