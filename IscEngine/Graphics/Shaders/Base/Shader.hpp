#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <GL/glew.h>
#include <GLM/glm.hpp>
using namespace glm;

namespace IscEngine {

	class Shader {

		private:

			GLuint id;

		public:

			Shader();
			~Shader();

			GLuint getId();

			void bind();
			void unbind();

			bool loadFromFiles(string vertexShader, string fragmentShader);
			bool loadFromStrings(string vertexShader, string fragmentShader);

			GLuint getUniformLocation(string uniform);
			GLuint getAttributeLocation(string attribute);

			template <class T> void setUniform(string uniform, T value0);
			template <class T> void setUniform(string uniform, T value0, T value1);
			template <class T> void setUniform(string uniform, T value0, T value1, T value2);
			template <class T> void setUniform(string uniform, T value0, T value1, T value2, T value3);
			void setUniformMatrix(string uniform, float* value);

	};

}