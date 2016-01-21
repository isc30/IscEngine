#include "Shader.hpp"

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

	// Fix to force template generation
	this->setUniform("", 0.f, 0.f, 0.f);
	this->setUniform("", 0);
	this->setUniform("", 0.f);

	this->setUniformArray("", 2, (void*)0);

	this->setUniform("", (unsigned int)0, (unsigned int)0);

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
template <class T> void Shader::setUniform(const char* const uniform, const T value0) const {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);
	
	if (typeid(T) == typeid(double)) glUniform1d(uniformLocation, (double)value0);
	else if (typeid(T) == typeid(float)) glUniform1f(uniformLocation, (float)value0);
	else if (typeid(T) == typeid(int)) glUniform1i(uniformLocation, (int)value0);
	else if (typeid(T) == typeid(unsigned int)) glUniform1ui(uniformLocation, (unsigned int)value0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(const char* const uniform, const T value0, const T value1) const {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);

	if (typeid(T) == typeid(double)) glUniform2d(uniformLocation, (double)value0, (double)value1);
	else if (typeid(T) == typeid(float)) glUniform2f(uniformLocation, (float)value0, (float)value1);
	else if (typeid(T) == typeid(int)) glUniform2i(uniformLocation, (int)value0, (int)value1);
	else if (typeid(T) == typeid(unsigned int)) glUniform2ui(uniformLocation, (unsigned int)value0, (unsigned int)value1);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(const char* const uniform, const T value0, const T value1, const T value2) const {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);

	if (typeid(T) == typeid(double)) glUniform3d(uniformLocation, (double)value0, (double)value1, (double)value2);
	else if (typeid(T) == typeid(float)) glUniform3f(uniformLocation, (float)value0, (float)value1, (float)value2);
	else if (typeid(T) == typeid(int)) glUniform3i(uniformLocation, (int)value0, (int)value1, (int)value2);
	else if (typeid(T) == typeid(unsigned int)) glUniform3ui(uniformLocation, (unsigned int)value0, (unsigned int)value1, (unsigned int)value2);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(const char* const uniform, const T value0, const T value1, const T value2, const T value3) const {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);

	if (typeid(T) == typeid(double)) glUniform4d(uniformLocation, (double)value0, (double)value1, (double)value2, (double)value3);
	else if (typeid(T) == typeid(float)) glUniform4f(uniformLocation, (float)value0, (float)value1, (float)value2, (float)value3);
	else if (typeid(T) == typeid(int)) glUniform4i(uniformLocation, (int)value0, (int)value1, (int)value2, (int)value3);
	else if (typeid(T) == typeid(unsigned int)) glUniform4ui(uniformLocation, (unsigned int)value0, (unsigned int)value1, (unsigned int)value2, (unsigned int)value3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform matrix
void Shader::setUniformMatrix(const char* const uniform, const float* const value) const {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value);

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