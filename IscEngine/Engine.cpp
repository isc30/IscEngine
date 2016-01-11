#include "Engine.hpp"
#include "Utils\Log.hpp"
using namespace IscEngine;

#include <chrono>

Engine::Engine() {

}

Engine::~Engine() {

	delete this->currentScene;
	delete this->window;

}

Window* Engine::getWindow() {

	return this->window;

}

void Engine::create(string title, uint width, uint height, uint style) {

	Log::cout << endl;
	Log::cout << " IscEngine" << endl;
	Log::cout << " -----------------------" << endl << endl;
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
	Log::cout << "  >> Depth: " << contextSettings.depthBits;
	Log::cout << ", Stencil: " << contextSettings.stencilBits;
	Log::cout << ", Antialiasing: " << contextSettings.antialiasingLevel << endl << endl;

	if (contextSettings.majorVersion < 2 || (contextSettings.majorVersion == 2 && contextSettings.minorVersion < 1)) {
		Log::cout << "No compatible graphics card found" << std::endl;
	}

	this->setupOpenGL();

}

void Engine::setupOpenGL() {

	if (glewInit() != GLEW_OK) {
		cerr << "Error initializing GLEW" << endl;
	}

	// Clear color
	glClearColor(1.0f, 0.7f, 0.1f, 1.0f);

	// Backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Depth control
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Engine::loop() {

	while (this->window->isOpen()) {

		SceneEvent sceneEvent;
		while (this->currentScene->pollEvent(sceneEvent)) {

			switch (sceneEvent.type) {

				case SceneEventType::SCENE_END:
					this->setScene((Scene*) sceneEvent.data);
					break;

			}

		}

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

				case sf::Event::KeyPressed:
					if (windowEvent.key.code == sf::Keyboard::Escape) this->window->close();
					break;

			}

			this->currentScene->processEvent(windowEvent);

		}

		this->currentScene->loop();

	}

}

void Engine::run() {

	this->loop();

}

void Engine::setScene(Scene* scene) {

	delete this->currentScene;
	this->currentScene = scene;

}