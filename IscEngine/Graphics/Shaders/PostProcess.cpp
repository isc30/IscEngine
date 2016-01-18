#include "PostProcess.hpp"
using namespace IscEngine;

Mesh* PostProcess::quad = new Mesh(vector<float>({
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0
}));

void PostProcess::render(Texture* const texture) {

	Texture::bind(texture);
	PostProcess::quad->render(GL_TRIANGLES);
	Texture::unbind();

}