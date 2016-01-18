#include "PostProcess.hpp"
using namespace IscEngine;

Mesh* PostProcess::quad = nullptr;

void PostProcess::render(Texture* const texture) {

	if (PostProcess::quad == nullptr) PostProcess::quad = new Mesh(vector<vec3>({vec3(-1,-1,0),vec3(1,-1,0),vec3(-1,1,0),vec3(-1,1,0),vec3(1,-1,0),vec3(1,1,0)}));

	Texture::bind(texture);
	PostProcess::quad->render(GL_TRIANGLES);
	Texture::unbind();

}