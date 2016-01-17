#pragma once

#include <GL/glew.h>
#include <vector>
using namespace std;

namespace IscEngine {

	// OpenGL Buffer Wrapper
	class Buffer {

		private:

			unsigned int id;
			unsigned int size;
			unsigned int componentCount;

		public:
			
			// Binds the Buffer
			static void bind(const Buffer* const buffer); // const pointer to const buffer
			// Unbinds the Buffer
			static void unbind();

			//////////////////////////////////////////////////////////////////////////////////////////////

			// Creates the Buffer
			Buffer(const vector<float>& data, const unsigned int componentCount);
			// Destroys the Buffer
			~Buffer();

			// Returns buffer size
			unsigned int getSize() const;
			// Returns Buffer component count (3 if vec3, 2 if vec2, ...)
			unsigned int getComponentCount() const;

	};

}