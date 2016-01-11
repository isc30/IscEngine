#pragma once

#include <iostream>
#include <fstream> // Files
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

	class Engine {

		private:

			Window* window;
			Scene* currentScene;
			
			void loop();
			void setupOpenGL();

		public:

			Engine();
			~Engine();

			void create(string title, uint width, uint height, uint style);
			void setScene(Scene* scene);
			void run();

			Window* getWindow();

	};

}