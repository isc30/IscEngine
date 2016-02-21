#pragma once

#include <vector>
#include <list>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "../../../World/Entities/StaticEntity.hpp"

namespace IscEngine { namespace Renderers {

	class Renderer {

		public:

		list<StaticEntity*> entities;

		public:

		Renderer();
		virtual ~Renderer();

		void clearEntities();
		void addEntity(StaticEntity* const entity);
		void addEntities(const vector<StaticEntity*>& entities);
		void addEntities(const list<StaticEntity*>& entities);
		void removeEntity(StaticEntity* const entity);

		virtual void render(mat4 P, mat4 V);

	};

} }