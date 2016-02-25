#pragma once

#include "Entity.hpp"
#include "../../Views/Cameras/Base/Camera.hpp"
#include "../../Graphics/Models/Model.hpp"
using namespace IscEngine::Graphics;

#include <map>
using namespace std;

namespace IscEngine {

	class StaticEntity : public Entity {

		private:
			
			map<float, Model*> models;

		public:
			
			StaticEntity(Model* const model);
			
			Model* getModel(const float distance);
			void addModel(const float distance, Model* const model);

	};

}