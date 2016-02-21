#include "Simple3D.hpp"
#include "../Resource.hpp"
using namespace IscEngine;
using namespace IscEngine::Renderers;

#include <iostream>
#include <string>

Simple3D::Simple3D() : Renderer::Renderer() {

	this->shader = Resource::load<Shader>("Simple3D.vsh", "Simple3D.fsh");

}

Simple3D::~Simple3D() {



}

void Simple3D::addLightSource(LightSource* const light) {

	this->lightSetup.add(light);

}

void Simple3D::addLightSource(const vector<LightSource*>& light) {

	this->lightSetup.add(light);

}

void Simple3D::addLightSource(const list<LightSource*>& light) {

	this->lightSetup.add(light);

}

void Simple3D::removeLightSource(LightSource* const light) {

	this->lightSetup.remove(light);

}

void Simple3D::clearLightSource() {

	this->lightSetup.clear();

}

void Simple3D::render(const mat4& P, const Camera* const camera) {

	vec3 cameraPosition = camera->getPosition();
	mat4 V = camera->getView();
	
	//Shader::bind(this->shader);

	Shader::currentShader->setUniformMatrix("V", &V[0][0]);
	Shader::currentShader->setUniformMatrix("P", &P[0][0]);
	Shader::currentShader->setUniform("cameraPosition_worldspace", cameraPosition.x, cameraPosition.y, cameraPosition.z);

	auto currentLightSetup = this->lightSetup.getLightSources();

	unsigned int i = 0;
	for (auto it = currentLightSetup.begin(), end = currentLightSetup.end(); it != end; ++it, ++i) {
		Shader::currentShader->setUniform(("lights[" + std::to_string(i) + "].position_worldspace").c_str(), (*it)->position.x, (*it)->position.y, (*it)->position.z);
		Shader::currentShader->setUniform(("lights[" + std::to_string(i) + "].color").c_str(), (*it)->color.r, (*it)->color.g, (*it)->color.b);
		Shader::currentShader->setUniform(("lights[" + std::to_string(i) + "].power").c_str(), (*it)->power);
	}

	for (auto it = this->entities.begin(), end = this->entities.end(); it != end; ++it) {

		vec4 model_cameraspace = P * V * (*it)->getModelMatrix() * vec4(0, 4, 0, 1);

		if (model_cameraspace.z >= 0.f && model_cameraspace.z <= 1000.0f &&
			model_cameraspace.x / model_cameraspace.w >= -1.f && model_cameraspace.x / model_cameraspace.w <= 1.f &&
			model_cameraspace.y / model_cameraspace.w >= -1.f && model_cameraspace.y / model_cameraspace.w <= 1.f) {

			Shader::currentShader->setUniformMatrix("M", &(*it)->getModelMatrix()[0][0]);

			(*it)->render(model_cameraspace.z);

		}

	}

	//Shader::unbind();

}