#pragma once

#include <GL/glew.h>
#include <vector>
using namespace std;

namespace IscEngine {

	// OpenGL IndexBuffer Wrapper
	class IndexBuffer {

		private:

			unsigned int id;
			unsigned int size;
			unsigned int type;

		public:
			
			// Binds the IndexBuffer
			static void bind(const IndexBuffer* const indexBuffer);
			// Unbinds the IndexBuffer
			static void unbind();

			//////////////////////////////////////////////////////////////////////////////////////////////

			// Creates the IndexBuffer
			IndexBuffer(const vector<unsigned short>& data);
			// Creates the IndexBuffer
			IndexBuffer(const vector<unsigned int>& data);
			// Destroys the IndexBuffer
			~IndexBuffer();

			// Returns the size
			unsigned int getSize() const;
			// Returns the type
			unsigned int getType() const;

	};

}