#include "SkyBox.hpp"
#include "../Views/ModelView.hpp"
#include "../Graphics/Shaders/Base/Shader.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////////////////////////////
// Static Content
//////////////////////////////////////////////////////////////////////////////////////////////

Mesh* SkyBox::cube = nullptr;
mat4 SkyBox::M = ModelView::getModelView();

//////////////////////////////////////////////////////////////////////////////////////////////
// Initializes the static variables of the class
void SkyBox::initializeStatic() {

	SkyBox::cube = new Mesh(vector<vec3>({

		vec3(-1.0f,  1.0f, -1.0f),
		vec3(-1.0f, -1.0f, -1.0f),
		vec3(1.0f, -1.0f, -1.0f),
		vec3(1.0f, -1.0f, -1.0f),
		vec3(1.0f,  1.0f, -1.0f),
		vec3(-1.0f,  1.0f, -1.0f),
		vec3(-1.0f, -1.0f,  1.0f),
		vec3(-1.0f, -1.0f, -1.0f),
		vec3(-1.0f,  1.0f, -1.0f),
		vec3(-1.0f,  1.0f, -1.0f),
		vec3(-1.0f,  1.0f,  1.0f),
		vec3(-1.0f, -1.0f,  1.0f),

		vec3(1.0f, -1.0f, -1.0f),
		vec3(1.0f, -1.0f,  1.0f),
		vec3(1.0f,  1.0f,  1.0f),
		vec3(1.0f,  1.0f,  1.0f),
		vec3(1.0f,  1.0f, -1.0f),
		vec3(1.0f, -1.0f, -1.0f),

		vec3(-1.0f, -1.0f,  1.0f),
		vec3(-1.0f,  1.0f,  1.0f),
		vec3(1.0f,  1.0f,  1.0f),
		vec3(1.0f,  1.0f,  1.0f),
		vec3(1.0f, -1.0f,  1.0f),
		vec3(-1.0f, -1.0f,  1.0f),

		vec3(-1.0f,  1.0f, -1.0f),
		vec3(1.0f,  1.0f, -1.0f),
		vec3(1.0f,  1.0f,  1.0f),
		vec3(1.0f,  1.0f,  1.0f),
		vec3(-1.0f,  1.0f,  1.0f),
		vec3(-1.0f,  1.0f, -1.0f),

		vec3(-1.0f, -1.0f, -1.0f),
		vec3(-1.0f, -1.0f,  1.0f),
		vec3(1.0f, -1.0f, -1.0f),
		vec3(1.0f, -1.0f, -1.0f),
		vec3(-1.0f, -1.0f,  1.0f)

	}));

	/*SkyBox::cube->addIndices(vector<unsigned short>({
		0, 1, 2,
		2, 1, 3
	}));*/

}

void SkyBox::render() {

	glDepthMask(GL_FALSE);
	//Shader::currentShader->setUniformMatrix("M", &M[0][0]);
	SkyBox::cube->render(GL_TRIANGLES);
	glDepthMask(GL_TRUE);

}