#include "Engine.hpp"
using namespace IscEngine;

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

	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;
	contextSettings.antialiasingLevel = 0;

	this->window = new Window(sf::VideoMode(width, height), title, style, contextSettings);
	this->window->setVerticalSyncEnabled(false);
	//this->window->setFramerateLimit(144);

	#ifdef DEBUG
		contextSettings = window->getSettings();
		cout << "OpenGL Version: " << contextSettings.majorVersion << "." << contextSettings.minorVersion << endl;
		cout << "Depth bits: " << contextSettings.depthBits << endl;
		cout << "Stencil bits: " << contextSettings.stencilBits << endl;
		cout << "Antialiasing: " << contextSettings.antialiasingLevel << endl;
	#endif

	this->setupOpenGL();

}

void Engine::setupOpenGL() {

	if (glewInit() != GLEW_OK) {
		cerr << "Error initializing GLEW" << endl;
	}

	// Clear color
	glClearColor(1.0f, 0.7f, 0.1f, 1.0f);

	/* Backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);*/

	// Depth control
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

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