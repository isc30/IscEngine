#pragma once

#include "Mesh.hpp"
#include "../Materials/Material.hpp"
using namespace IscEngine::Graphics::Materials;

namespace IscEngine { namespace Graphics {

	struct Model {

		Mesh* mesh;
		Material* material;

	};

} }