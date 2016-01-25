#pragma once

#include "Entity.hpp"
#include "../../Graphics/Models/Mesh.hpp"
#include "../../Views/Cameras/Base/Camera.hpp"

#include <map>
using namespace std;

namespace IscEngine {

	class StaticEntity : public Entity {

		private:
			
			map<float, Mesh*> meshes;

		public:
			
			StaticEntity(Mesh* const mesh);
			
			void addMesh(const float distance, Mesh* const mesh);
			void render(mat4& VP);

	};

}