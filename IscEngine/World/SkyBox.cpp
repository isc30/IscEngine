#include "SkyBox.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////////////////////////////
// Static Content
//////////////////////////////////////////////////////////////////////////////////////////////

Mesh* SkyBox::cube = nullptr;

//////////////////////////////////////////////////////////////////////////////////////////////
// Initializes the static variables of the class
void SkyBox::initializeStatic() {

	SkyBox::cube = new Mesh(vector<vec3>({
		vec3(-1, -1, 0),
		vec3(1, -1, 0),
		vec3(-1, 1, 0),
		vec3(-1, 1, 0),
		vec3(1, -1, 0),
		vec3(1, 1, 0)
	}));

	SkyBox::cube->addIndices(vector<unsigned short>({
		0, 1, 2,
		2, 1, 3
	}));

}

void SkyBox::render(const Texture* const front, const Texture* const back, const Texture* const right, const Texture* const left, const Texture* const up, const Texture* const down) {



}