#include "Engine.hpp"
#include "Utils\Log.hpp"
using namespace IscEngine;

#include <chrono>

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
Engine::Engine() {

	Log::cout << endl;
	Log::cout << " IscEngine" << endl;
	Log::cout << " -----------------------" << endl << endl;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
Engine::~Engine() {

	delete this->currentScene; this->currentScene = nullptr;
	delete this->window; this->window = nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns the Window
Window* Engine::getWindow() const {

	return this->window;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Creates a Window
void Engine::create(const string& title, const unsigned int width, const unsigned int height, const unsigned int style) {

	Log::cout << " Creating context..." << endl << endl;

	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;
	contextSettings.antialiasingLevel = 0;
	contextSettings.majorVersion = 2;
	contextSettings.minorVersion = 1;

	this->window = new Window(sf::VideoMode(width, height), title, style, contextSettings);
	this->window->setVerticalSyncEnabled(false);
	//this->window->setFramerateLimit(144);

	contextSettings = window->getSettings();
	Log::cout << "  >> " << glGetString(GL_VENDOR) << " | " << glGetString(GL_RENDERER) << endl;
	Log::cout << "  >> OpenGL " << contextSettings.majorVersion << "." << contextSettings.minorVersion << endl;
	Log::cout << "  >> Depth: " << contextSettings.depthBits << ", Stencil: " << contextSettings.stencilBits << ", Antialiasing: " << contextSettings.antialiasingLevel << endl;

	if (contextSettings.majorVersion < 2 || (contextSettings.majorVersion == 2 && contextSettings.minorVersion < 1)) {
		Log::cout << std::endl << "  ## No compatible graphics card found" << std::endl;
		return;
	}

	Log::cout << endl;

	this->setupOpenGL();

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Setups OpenGL (glew, ...)
void Engine::setupOpenGL() {

	Log::cout << " Initializing GLEW..." << endl << endl;

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		Log::cout << "  >> Error initializing GLEW" << endl;
	} else {
		Log::cout << "  >> Using GLEW v" << glewGetString(GLEW_VERSION) << endl;
	}

	if (GLEW_ARB_vertex_array_object) {
		Log::cout << "  >> Using VAO" << endl;
	} else {
		Log::cout << "  >> Using VBO :'(" << endl;
	}

	Log::cout << endl;

	// Clear color
	glClearColor(1.0f, 0.7f, 0.1f, 1.0f);

	// Backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Depth control
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

}

//////////////////////////////////////////////////////////////////////////////////////////////
// GameLoop
void Engine::loop() {

	while (this->window->isOpen()) {

		sf::Event windowEvent;
		while (this->window->pollEvent(windowEvent)) {

			switch (windowEvent.type) {

				case sf::Event::Closed:
					this->window->close();
					break;

				case sf::Event::Resized:
					glViewport(0, 0, windowEvent.size.width, windowEvent.size.height);
					break;

				case sf::Event::GainedFocus:
					this->window->setFocus(true);
					break;

				case sf::Event::LostFocus:
					this->window->setFocus(false);
					break;

			}

			if (this->currentScene != nullptr) this->currentScene->processEvent(windowEvent);

		}

		SceneEvent sceneEvent;
		while (this->currentScene != nullptr && this->currentScene->pollEvent(sceneEvent)) {

			if (sceneEvent.type == SceneEventType::SCENE_END) {

				if (sceneEvent.data != nullptr) {
					this->setScene((Scene*)sceneEvent.data);
				} else {
					delete this->currentScene; this->currentScene = nullptr;
					window->close();
				}

			}

		}

		if (this->currentScene != nullptr) this->currentScene->loop();

	}

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Runs the GameLoop
void Engine::run() {

	this->loop();

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Changes the current Scene
void Engine::setScene(Scene* const scene) {

	delete this->currentScene; this->currentScene = nullptr;
	this->currentScene = scene;

}