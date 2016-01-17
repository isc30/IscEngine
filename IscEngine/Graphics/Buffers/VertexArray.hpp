#pragma once

#include <vector>
using namespace std;

#include "Buffer.hpp"

namespace IscEngine {

	// OpenGL VertexArray Wrapper
	class VertexArray {

		private:

			unsigned int id;
			vector<Buffer*> buffers;

		public:
			
			// Binds the VertexArray
			static void bind(const VertexArray* const vertexArray);
			// Unbinds the VertexArray
			static void unbind();

			//////////////////////////////////////////////////////////////////////////////////////////////
			
			// Creates the VertexArray
			VertexArray();
			// Destroys the VertexArray
			~VertexArray();

			// Adds a Buffer in a index
			void addBuffer(Buffer* const buffer, const unsigned int index);

	};

}