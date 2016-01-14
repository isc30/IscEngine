#pragma once

#include <vector>
using namespace std;

#include "Buffer.hpp"

namespace IscEngine {

	class VertexArray {

		private:

			unsigned int id;
			vector<Buffer*> buffers;

		public:

			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, const unsigned int index);

			void bind() const;
			void unbind() const;

	};

}