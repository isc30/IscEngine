#pragma once

#include <GL/glew.h>
#include <vector>
using namespace std;

namespace IscEngine {

	class FrameBuffer {

		private:

			unsigned int id;
			// Texture texture;

		public:

			FrameBuffer(/*Texture*/);
			~FrameBuffer();

			//const Texture getTexture() const;

			static void bind(const FrameBuffer& frameBuffer);
			static void unbind();

	};

}