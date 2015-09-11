#pragma once

#include <GL/glew.h>
#include <vector>
using namespace std;

namespace IscEngine {

	class IndexBuffer {

		private:

			GLuint id;
			GLuint count;

		public:

			IndexBuffer(vector<GLushort> data);
			IndexBuffer(vector<GLuint> data);
			~IndexBuffer();

			void bind();
			void unbind();

			GLuint getCount() { return this->count; }

	};

}