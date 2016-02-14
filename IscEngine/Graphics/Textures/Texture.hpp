#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
#include <glm/vec2.hpp>
using namespace glm;
#include <GL/glew.h>

namespace IscEngine {

	class Texture {

		private:

			unsigned int id;
			unsigned int width, height;

		public:

			// Binds the Texture in the index
			static void bind(const Texture* const texture, const unsigned int index = GL_TEXTURE0, unsigned int type = GL_TEXTURE_2D);
			// Unbinds the Texture
			static void unbind(const unsigned int index = GL_TEXTURE0, unsigned int type = GL_TEXTURE_2D);

			//////////////////////////////////////////////////////////////////////////////////////////////

			Texture();
			~Texture();

			unsigned int getId() const { return this->id; }
			unsigned int getWidth() const { return this->width; }
			unsigned int getHeight() const { return this->height; }

			bool loadFromFile(const string& fileName);
			bool loadCubeMap(const vector<string>& fileNames);
			void create(const unsigned int width, const unsigned int height, const bool color = true, const bool depth = false);

	};

}
