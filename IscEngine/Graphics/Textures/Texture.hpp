#pragma once

#include <SFML/Graphics.hpp>
#include <GL/glew.h>

namespace IscEngine {

	class Texture {

		private:

			unsigned int id;
			
		public:
			
			// Binds the Texture in the index
			static void bind(const Texture* const texture, const unsigned int index = GL_TEXTURE0);
			// Unbinds the Texture
			static void unbind(const unsigned int index = GL_TEXTURE0);

			//////////////////////////////////////////////////////////////////////////////////////////////

			Texture();
			~Texture();

			bool loadFromFile(const char* const fileName);
			void create(const unsigned int width, const unsigned int height, const bool color = true, const bool depth = false);

	};

}