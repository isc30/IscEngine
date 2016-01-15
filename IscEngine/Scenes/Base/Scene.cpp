#include "Scene.hpp"
using namespace IscEngine;

Scene::Scene(Window* window) {

	this->window = window;

}

void Scene::pushEvent(const SceneEvent& sceneEvent) {

	this->sceneEventQueue.push(sceneEvent);

}

const bool Scene::pollEvent(SceneEvent& sceneEvent) {

	if (this->sceneEventQueue.empty()) return false;

	sceneEvent = this->sceneEventQueue.front();
	this->sceneEventQueue.pop();

	return true;

}

void Scene::loop() {

	sf::Time startTime = this->sceneClock.getElapsedTime();

	this->update();
	this->render();

	////////////////////////////////////////////////////////////////////////////////////////
	// Custom fps limiter

	/*
	float fps = 144;

	if ((this->sceneClock.getElapsedTime() - startTime).asSeconds() < 1 / fps) {

		sf::sleep(sf::seconds(1 / fps - (this->sceneClock.getElapsedTime() - startTime).asSeconds()));

	}
	*/

	this->deltaTime = this->sceneClock.getElapsedTime() - startTime;

}

void Scene::endScene(Scene* scene) {

	SceneEvent sceneEvent;
	sceneEvent.type = SCENE_END;
	sceneEvent.data = (void*)scene;

	this->pushEvent(sceneEvent);

}