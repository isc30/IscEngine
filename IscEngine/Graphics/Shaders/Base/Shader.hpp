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

			void setUniform(const char* const uniform, const double value0) const; // Sets a shader uniform value
			void setUniform(const char* const uniform, const float value0) const; // Sets a shader uniform value
			void setUniform(const char* const uniform, const int value0) const; // Sets a shader uniform value
			void setUniform(const char* const uniform, const unsigned int value0) const; // Sets a shader uniform value
			
			void setUniform(const char* const uniform, const double value0, const double value1) const; // Sets a shader uniform value
			void setUniform(const char* const uniform, const float value0, const float value1) const; // Sets a shader uniform value
			void setUniform(const char* const uniform, const int value0, const int value1) const; // Sets a shader uniform value
			void setUniform(const char* const uniform, const unsigned int value0, const unsigned int value1) const; // Sets a shader uniform value
			
			void setUniform(const char* const uniform, const double value0, const double value1, const double value2) const; // Sets a shader uniform value
			void setUniform(const char* const uniform, const float value0, const float value1, const float value2) const; // Sets a shader uniform value
			void setUniform(const char* const uniform, const int value0, const int value1, const int value2) const; // Sets a shader uniform value
			void setUniform(const char* const uniform, const unsigned int value0, const unsigned int value1, const unsigned int value2) const; // Sets a shader uniform value
			
			void setUniform(const char* const uniform, const double value0, const double value1, const double value2, const double value3) const;
			void setUniform(const char* const uniform, const float value0, const float value1, const float value2, const float value3) const;
			void setUniform(const char* const uniform, const int value0, const int value1, const int value2, const int value3) const;
			void setUniform(const char* const uniform, const unsigned int value0, const unsigned int value1, const unsigned int value2, const unsigned int value3) const;

			// Sets a shader uniform array
			template <class T> void setUniformArray(const char* const uniform, const unsigned int size, const T* const pointer) const;

			// Sets a shader uniform matrix
			void setUniformMatrix(const char* const uniform, const float* const value) const;

	};

}