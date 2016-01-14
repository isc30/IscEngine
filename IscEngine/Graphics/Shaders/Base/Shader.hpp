#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLM/glm.hpp>
using namespace glm;

namespace IscEngine {

	class Shader {

		private:

			unsigned int id;

		public:
			
			// Static
			static Shader* currentShader;

			// Dynamic
			Shader();
			~Shader();

			const unsigned int getId() const;

			void bind() const;
			void unbind() const;

			const bool loadFromFiles(const string& vertexShader, const string& fragmentShader);
			const bool loadFromStrings(const char* vertexShader, const char* fragmentShader);

			const int getUniformLocation(const char* uniform) const;
			const int getAttributeLocation(const char* attribute) const;

			template <class T> void setUniform(const char* uniform, T value0);
			template <class T> void setUniform(const char* uniform, T value0, T value1);
			template <class T> void setUniform(const char* uniform, T value0, T value1, T value2);
			template <class T> void setUniform(const char* uniform, T value0, T value1, T value2, T value3);
			void setUniformMatrix(const char* uniform, float* value);
			template <class T> void setUniformArray(const char* uniform, uint size, T* pointer);
			template <class T> void setUniformVector(const char* uniform, vector<T>* vector);

	};

}