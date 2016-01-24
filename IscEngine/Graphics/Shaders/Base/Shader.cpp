#include "Shader.hpp"

#include <typeinfo>
#include <fstream>
#include <sstream>
using namespace std;

#include <GL/glew.h>
#include <GLM/glm.hpp>
using namespace glm;

#include "../../../Utils/Log.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////////////////////////////
// Initialize static variables
//////////////////////////////////////////////////////////////////////////////////////////////

Shader* Shader::currentShader = nullptr;

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
Shader::Shader() {

	this->id = 0;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
Shader::~Shader() {

	Log::cout << "Deleting shader " << this->id << endl;
	glDeleteProgram(this->id);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Binds the shader
void Shader::bind(Shader* const shader) {

	glUseProgram(shader->id);
	Shader::currentShader = shader;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Unbinds the shader
void Shader::unbind() {

	glUseProgram(0);
	Shader::currentShader = nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns shader uniform location
int Shader::getUniformLocation(const char* const uniform) const {

	return glGetUniformLocation(this->id, uniform);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns shader attribute location
int Shader::getAttributeLocation(const char* const attribute) const {

	return glGetAttribLocation(this->id, attribute);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const double value0) const {
	
	glUniform1d(this->getUniformLocation(uniform), value0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const float value0) const {

	glUniform1f(this->getUniformLocation(uniform), value0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const int value0) const {

	glUniform1i(this->getUniformLocation(uniform), value0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const unsigned int value0) const {

	glUniform1ui(this->getUniformLocation(uniform), value0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const double value0, const double value1) const {

	glUniform2d(this->getUniformLocation(uniform), value0, value1);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const float value0, const float value1) const {

	glUniform2f(this->getUniformLocation(uniform), value0, value1);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const int value0, const int value1) const {

	glUniform2i(this->getUniformLocation(uniform), value0, value1);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const unsigned int value0, const unsigned int value1) const {

	glUniform2ui(this->getUniformLocation(uniform), value0, value1);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const double value0, const double value1, const double value2) const {

	glUniform3d(this->getUniformLocation(uniform), value0, value1, value2);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const float value0, const float value1, const float value2) const {

	glUniform3f(this->getUniformLocation(uniform), value0, value1, value2);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const int value0, const int value1, const int value2) const {

	glUniform3i(this->getUniformLocation(uniform), value0, value1, value2);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const unsigned int value0, const unsigned int value1, const unsigned int value2) const {

	glUniform3ui(this->getUniformLocation(uniform), value0, value1, value2);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const double value0, const double value1, const double value2, const double value3) const {

	glUniform4d(this->getUniformLocation(uniform), value0, value1, value2, value3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const float value0, const float value1, const float value2, const float value3) const {

	glUniform4f(this->getUniformLocation(uniform), value0, value1, value2, value3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const int value0, const int value1, const int value2, const int value3) const {

	glUniform4i(this->getUniformLocation(uniform), value0, value1, value2, value3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
void Shader::setUniform(const char* const uniform, const unsigned int value0, const unsigned int value1, const unsigned int value2, const unsigned int value3) const {

	glUniform4ui(this->getUniformLocation(uniform), value0, value1, value2, value3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform matrix
void Shader::setUniformMatrix(const char* const uniform, const float* const value) const {
	
	glUniformMatrix4fv(this->getUniformLocation(uniform), 1, GL_FALSE, value);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform array
template <class T> void Shader::setUniformArray(const char* const uniform, const unsigned int size, const T* const pointer) const {

	if (uniform == "") return;
	unsigned int uniformLocation = this->getUniformLocation(uniform);

	if (typeid(T) == typeid(double)) glUniform3dv(uniformLocation, size, (const double*)pointer);
	else if (typeid(T) == typeid(float)) glUniform3fv(uniformLocation, size, (const float*) pointer);
	else if (typeid(T) == typeid(int)) glUniform3iv(uniformLocation, size, (const int*) pointer);
	else if (typeid(T) == typeid(unsigned int)) glUniform3uiv(uniformLocation, size, (const unsigned int*)pointer);

}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Loads shader from a String and returns if success
bool Shader::loadFromStrings(const char* const vertexShader, const char* const fragmentShader) {

	// Support to vertex + fragment shader
	// Geometry shader not supported
	unsigned int programId = glCreateProgram();
	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	int result = GL_FALSE;

	// Compile vertex Shader
	glShaderSource(vertexShaderId, 1, &vertexShader, 0);
	glCompileShader(vertexShaderId);

	#ifdef DEBUG
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
		Log::cout << "Vertex shader: " << (result ? "OK" : "ERROR") << endl;
	#endif

	// Compile fragment Shader
	glShaderSource(fragmentShaderId, 1, &fragmentShader, 0);
	glCompileShader(fragmentShaderId);

	#ifdef DEBUG
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
		Log::cout << "Fragment shader: " << (result ? "OK" : "ERROR") << endl;
	#endif

	// Link both shaders
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	// Clean memory
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	if (!result) {

		#ifdef DEBUG
				int errorLength;
				glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &errorLength);
				string errorMessage(errorLength, 1);
				glGetProgramInfoLog(programId, errorLength, 0, &errorMessage[0]);
				Log::cout << "Shader id " << programId << " error: " << endl << '\t' << errorMessage << endl;
		#endif

		glDeleteProgram(programId);
		return false;

	} else {

		this->id = programId;
		return true;

	}

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Loads shader from files and returns if success
bool Shader::loadFromFiles(const string& vertexShader, const string& fragmentShader) {

	string vertexShaderCode;
	ifstream vertexShaderFile(vertexShader);
	if (vertexShaderFile.is_open()) {
		string line;
		while (getline(vertexShaderFile, line)) {
			vertexShaderCode += '\n' + line;
		}
		vertexShaderFile.close();
	}

	string fragmentShaderCode;
	ifstream fragmentShaderFile(fragmentShader);
	if (fragmentShaderFile.is_open()) {
		string line;
		while (getline(fragmentShaderFile, line)) {
			fragmentShaderCode += '\n' + line;
		}
		fragmentShaderFile.close();
	}

	return this->loadFromStrings(vertexShaderCode.c_str(), fragmentShaderCode.c_str());

}