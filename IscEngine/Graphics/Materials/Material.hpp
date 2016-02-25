#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include "../Textures/Texture.hpp"

namespace IscEngine { namespace Graphics { namespace Materials {

	struct MaterialProperties {

		float shininess = 10.f;
		vec3 specular = vec3(1, 1, 1);

	};

	class Material {

	private:

		Texture* texture;
		Texture* normalMap;
		Texture* specularMap;
		MaterialProperties materialProperties;
		
	public:

		Texture* getTexture() const { return this->texture; }
		void setTexture(Texture* const texture) { this->texture = texture; }

		Texture* getNormalMap() const { return this->normalMap; }
		void setNormalMap(Texture* const normalMap) { this->normalMap = normalMap; }

		Texture* getSpecularMap() const { return this->specularMap; }
		void setSpecularMap(Texture* const specularMap) { this->specularMap = specularMap; }

		MaterialProperties getMaterialProperties() { return this->materialProperties; }
		void setMaterialProperties(MaterialProperties materialProperties) { this->materialProperties = materialProperties; }

	};

} } }