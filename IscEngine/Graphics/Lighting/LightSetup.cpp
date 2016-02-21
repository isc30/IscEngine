#include "LightSetup.hpp"
using namespace IscEngine::Graphics::Lighting;

void LightSetup::add(LightSource* const light) {

	this->lightSources.push_back(light);

}

void LightSetup::add(const list<LightSource*>& light) {

	this->lightSources.insert(this->lightSources.end(), light.begin(), light.end());

}

void LightSetup::add(const vector<LightSource*>& light) {

	this->lightSources.insert(this->lightSources.end(), light.begin(), light.end());

}

void LightSetup::remove(LightSource* const light) {

	this->lightSources.remove(light);

}

void LightSetup::clear() {

	this->lightSources.clear();

}