#pragma once

#include <GL/glew.h>
#include <vector>
using namespace std;

namespace IscEngine {

	class IndexBuffer {

		private:

			unsigned int id;
			unsigned int count;
			unsigned int type;

		public:

			IndexBuffer(const vector<unsigned short>& data);
			IndexBuffer(const vector<unsigned int>& data);
			~IndexBuffer();

			const unsigned int getCount() const;
			const unsigned int getType() const;

			void bind() const;
			void unbind() const;

	};

}