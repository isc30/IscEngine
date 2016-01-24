#pragma once

#include "Entity.hpp"
#include "../../Graphics/Models/Mesh.hpp"

namespace IscEngine {

	class StaticEntity : public Entity {

		private:

			Mesh* mesh;
			Mesh* lowPolyMesh;
			float lodDistance;

		public:
			
			StaticEntity();

			void setMesh(Mesh* const mesh);
			void setLowPolyMesh(Mesh* const lowPolyMesh);
			void setLodDistance(const float lodDistance);
			void render(mat4& VP);

	};

}