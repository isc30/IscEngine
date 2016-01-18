#pragma once

#include <GL/glew.h>
using namespace std;

#include "../Textures/Texture.hpp"

namespace IscEngine {

	// OpenGL FrameBuffer Wrapper
	class FrameBuffer {

		private:

			unsigned int id;
			Texture* texture;

		public:

			// Binds the FrameBuffer
			static void bind(const FrameBuffer* const frameBuffer);
			// Unbinds the FrameBuffer
			static void unbind();

			//////////////////////////////////////////////////////////////////////////////////////////////

			// Creates the FrameBuffer
			FrameBuffer(const unsigned int width, const unsigned int height, const bool color = true, const bool depth = false);
			// Destroys the FrameBuffer
			~FrameBuffer();

			Texture* getTexture() const { return this->texture; }

	};

}