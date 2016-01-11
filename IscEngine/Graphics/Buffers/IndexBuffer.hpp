#pragma once

#include <GL/glew.h>
#include <vector>
using namespace std;

namespace IscEngine {

	class IndexBuffer {

		private:

			unsigned int id;
			unsigned int count;

		public:

			IndexBuffer(vector<unsigned short> data);
			IndexBuffer(vector<unsigned int> data);
			~IndexBuffer();

			void bind();
			void unbind();

			unsigned int getCount() { return this->count; }

	};

}