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

void Simple3D::render(const mat4& P, const Camera* const camera) {

	vec3 cameraPosition = camera->getPosition();
	mat4 V = camera->getView();
	
	Shader::bind(this->shader);

	this->shader->setUniformMatrix("V", &V[0][0]);
	this->shader->setUniformMatrix("P", &P[0][0]);
	this->shader->setUniform("cameraPosition_worldspace", cameraPosition.x, cameraPosition.y, cameraPosition.z);

	auto currentLightSetup = this->lightSetup.getLightSources();
	this->shader->setUniform("lightCount", (int)currentLightSetup.size());

	unsigned int i = 0;
	for (auto it = currentLightSetup.begin(), end = currentLightSetup.end(); it != end; ++it, ++i) {
		string lightUniform = "lights[" + std::to_string(i) + "]";
		(*it)->setShaderUniforms(this->shader, lightUniform);
	}

	for (auto it = this->entities.begin(), end = this->entities.end(); it != end; ++it) {

		vec4 model_cameraspace = P * V * (*it)->getModelMatrix() * vec4(0, 4, 0, 1);

		/*if (model_cameraspace.z >= 0.f && model_cameraspace.z <= 1000.0f &&
			model_cameraspace.x / model_cameraspace.w >= -1.f && model_cameraspace.x / model_cameraspace.w <= 1.f &&
			model_cameraspace.y / model_cameraspace.w >= -1.f && model_cameraspace.y / model_cameraspace.w <= 1.f) {*/

			this->shader->setUniformMatrix("M", &(*it)->getModelMatrix()[0][0]);

			Model* model = (*it)->getModel(model_cameraspace.z);
			Material* material = model->material;
			Mesh* mesh = model->mesh;

			Texture::bind(material->texture, 0);
			this->shader->setUniform("textureSampler", 0);

			mesh->render(GL_TRIANGLES);

		//}

	}

	Texture::unbind(0);

	Shader::unbind();

}