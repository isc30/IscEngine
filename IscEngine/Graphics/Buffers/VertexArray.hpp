#pragma once

#include <vector>
using namespace std;
#include <GL/glew.h>

#include "Buffer.hpp"

namespace IscEngine {

	class VertexArray {

		private:

			unsigned int id;
			vector<Buffer*> buffers;
			vector<unsigned int> indexes;

		public:

			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, unsigned int index);

			void bind();
			void unbind();

	};

}