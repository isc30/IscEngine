#pragma once

#include <GL/glew.h>
#include <vector>
using namespace std;

namespace IscEngine {

	class Buffer {

		private:

			unsigned int id;
			unsigned int count;
			unsigned int componentCount;

		public:

			Buffer(const vector<float>& data, const unsigned int componentCount);
			~Buffer();

			const unsigned int getCount() const;
			const unsigned int getComponentCount() const;

			void bind() const;
			void unbind() const;

	};

}