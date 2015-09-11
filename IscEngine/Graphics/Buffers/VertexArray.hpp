#pragma once

#include <vector>
using namespace std;
#include <GL/glew.h>

#include "Buffer.hpp"

namespace IscEngine {

	class VertexArray {

		private:

			GLuint id;
			vector<Buffer*> buffers;

		public:

			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);

			void bind();
			void unbind();

	};

}