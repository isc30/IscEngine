#pragma once

#include "Mesh.hpp"
#include "../Materials/Material.hpp"
using namespace IscEngine::Graphics::Materials;

namespace IscEngine { namespace Graphics {

	class Model {

	private:

		Mesh* mesh;
		Material* material;

	public:

		Mesh* getMesh() const { return this->mesh; }
		void setMesh(Mesh* const mesh) { this->mesh = mesh; }

		Material* getMaterial() const { return this->material; }
		void setMaterial(Material* const material) { this->material = material; }

	};

} }