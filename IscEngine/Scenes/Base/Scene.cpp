#include "Scene.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
Scene::Scene(Window* window) {

	this->window = window;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Push new Scene Event
void Scene::pushEvent(const SceneEvent& sceneEvent) {

	this->sceneEventQueue.push(sceneEvent);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Polls the first Scene Event
bool Scene::pollEvent(SceneEvent& sceneEvent) {

	if (this->sceneEventQueue.empty()) return false;

	sceneEvent = this->sceneEventQueue.front();
	this->sceneEventQueue.pop();

	return true;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Updates and Renders the Scene while calculating deltaTime
void Scene::loop() {

	sf::Time startTime = this->sceneClock.getElapsedTime();

	this->update();
	this->render();

	////////////////////////////////////////////////////////////////////////////////////////
	// Custom fps limiter
	/*
	this->realDeltaTime = this->sceneClock.getElapsedTime() - startTime;
	float fps = 146;
	if ((this->sceneClock.getElapsedTime() - startTime).asSeconds() < 1 / fps) {
		sf::sleep(sf::seconds(1 / fps - (this->sceneClock.getElapsedTime() - startTime).asSeconds()));
	}*/
	
	this->deltaTime = this->sceneClock.getElapsedTime() - startTime;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Ends the Scene
void Scene::endScene(Scene* scene) {

	SceneEvent sceneEvent;
	sceneEvent.type = SCENE_END;
	sceneEvent.data = (void*)scene;

	this->pushEvent(sceneEvent);

}