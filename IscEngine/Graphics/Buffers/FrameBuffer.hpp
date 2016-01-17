#pragma once

#include <GL/glew.h>
using namespace std;

namespace IscEngine {

	// OpenGL FrameBuffer Wrapper
	class FrameBuffer {

		private:

			unsigned int id;
			// Texture texture;

		public:

			// Binds the FrameBuffer
			static void bind(const FrameBuffer* const frameBuffer);
			// Unbinds the FrameBuffer
			static void unbind();

			//////////////////////////////////////////////////////////////////////////////////////////////

			// Creates the FrameBuffer
			FrameBuffer(); // TODO: pass a Texture*
			// Destroys the FrameBuffer
			~FrameBuffer();

	};

}