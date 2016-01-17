#pragma once

#include <iostream>
#include <vector>
using namespace std;

namespace IscEngine {

	// OpenGL Shader Wrapper
	class Shader {

		private:
			
			unsigned int id;

		public:
			
			// Stores the current bound Shader
			static Shader* currentShader;
			// Binds the Shader
			static void bind(Shader* const shader);
			// Unbinds the Shader
			static void unbind();

			//////////////////////////////////////////////////////////////////////////////////////////////

			// Creates the Shader
			Shader();
			// Destructs the Shader
			~Shader();
			
			// Loads shader from files and returns if success
			bool loadFromFiles(const string& vertexShader, const string& fragmentShader);
			// Loads shader from a String and returns if success
			bool loadFromStrings(const char* const vertexShader, const char* const fragmentShader);

			// Returns shader uniform location
			int getUniformLocation(const char* const uniform) const;
			// Returns shader attribute location
			int getAttributeLocation(const char* const attribute) const;

			// Sets a shader uniform value
			template <class T> void setUniform(const char* const uniform, const T value0);
			// Sets a shader uniform value
			template <class T> void setUniform(const char* const uniform, const T value0, const T value1);
			// Sets a shader uniform value
			template <class T> void setUniform(const char* const uniform, const T value0, const T value1, const T value2);
			// Sets a shader uniform value
			template <class T> void setUniform(const char* const uniform, const T value0, const T value1, const T value2, const T value3);
			// Sets a shader uniform array
			template <class T> void setUniformArray(const char* const uniform, const unsigned int size, const T* const pointer);
			// Sets a shader uniform matrix
			void setUniformMatrix(const char* const uniform, const float* const value);

	};

}