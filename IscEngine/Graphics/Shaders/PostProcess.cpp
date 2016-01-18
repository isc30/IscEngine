#include "PostProcess.hpp"
using namespace IscEngine;

// Static Content
Mesh* PostProcess::quad = nullptr;

void PostProcess::initializeStatic() {

	PostProcess::quad = new Mesh(vector<vec3>({vec3(-1,-1,0),vec3(1,-1,0),vec3(-1,1,0),vec3(-1,1,0),vec3(1,-1,0),vec3(1,1,0)}));

}

void PostProcess::render(Texture* const texture) {

	Texture::bind(texture);
	PostProcess::quad->render(GL_TRIANGLES);
	Texture::unbind();

}