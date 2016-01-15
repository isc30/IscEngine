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

	/// <summary> OpenGL Shader Wrapper </summary>
	class Shader {

		private:
			
			unsigned int id;

		public:
			
			//////////////////////////////////////////////////////////////////////////////////////////////
			
			/// <summary> Stores the current bound Shader </summary>
			static Shader* currentShader;
			/// <summary> Binds one Shader </summary>
			static void bind(Shader& shader);
			/// <summary> Unbinds the Shader </summary>
			static void unbind();

			//////////////////////////////////////////////////////////////////////////////////////////////

			/// <summary> Constructor </summary>
			Shader();
			/// <summary> Destructor </summary>
			~Shader();
			
			/// <summary> Loads shader from files and returns if success </summary>
			const bool loadFromFiles(const string& vertexShader, const string& fragmentShader);
			/// <summary> Loads shader from a String and returns if success </summary>
			const bool loadFromStrings(const char* vertexShader, const char* fragmentShader);

			/// <summary> Returns shader uniform location </summary>
			const int getUniformLocation(const char* uniform) const;
			/// <summary> Returns shader attribute location </summary>
			const int getAttributeLocation(const char* attribute) const;

			/// <summary> Sets a shader uniform value </summary>
			template <class T> void setUniform(const char* uniform, T value0);
			/// <summary> Sets a shader uniform value </summary>
			template <class T> void setUniform(const char* uniform, T value0, T value1);
			/// <summary> Sets a shader uniform value </summary>
			template <class T> void setUniform(const char* uniform, T value0, T value1, T value2);
			/// <summary> Sets a shader uniform value </summary>
			template <class T> void setUniform(const char* uniform, T value0, T value1, T value2, T value3);
			/// <summary> Sets a shader uniform matrix </summary>
			void setUniformMatrix(const char* uniform, float* value);
			//template <class T> void setUniformArray(const char* uniform, uint size, T* pointer);

	};

}