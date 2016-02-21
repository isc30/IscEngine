#include "Simple3D.hpp"
#include "../Resource.hpp"
using namespace IscEngine;
using namespace IscEngine::Renderers;

Simple3D::Simple3D() : Renderer::Renderer() {

	this->shader = Resource::load<Shader>("Simple3D.vsh", "Simple3D.fsh");

}

Simple3D::~Simple3D() {



}

void Simple3D::render(mat4 P, mat4 V) {

	//Shader::bind(this->shader);

	Shader::currentShader->setUniformMatrix("V", &V[0][0]);
	Shader::currentShader->setUniformMatrix("P", &P[0][0]);

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