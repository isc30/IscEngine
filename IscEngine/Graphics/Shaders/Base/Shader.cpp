#include "Shader.hpp"
#include "../ShaderManager.hpp"
#include "../../../Utils/Log.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////////////////////////////
// Default constructor
Shader::Shader() {

	this->id = 0;

	// Fix for template generation
	this->setUniform("", 0.f, 0.f, 0.f);
	this->setUniform("", 0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
Shader::~Shader() {

	glDeleteProgram(this->id);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns the id
GLuint Shader::getId() {

	return this->id;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Binds the shader
void Shader::bind() {

	glUseProgram(this->id);
	ShaderManager::currentShader = this;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Unbinds the shader
void Shader::unbind() {

	glUseProgram(0);
	ShaderManager::currentShader = nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns shader uniform location
int Shader::getUniformLocation(string uniform) {

	return glGetUniformLocation(this->id, uniform.c_str());

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns shader attribute location
int Shader::getAttributeLocation(string attribute) {

	return glGetAttribLocation(this->id, attribute.c_str());

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(string uniform, T value0) {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);
	
	if (typeid(T) == typeid(double)) glUniform1d(uniformLocation, value0);
	else if (typeid(T) == typeid(float)) glUniform1f(uniformLocation, value0);
	else if (typeid(T) == typeid(int)) glUniform1i(uniformLocation, value0);
	else if (typeid(T) == typeid(uint)) glUniform1ui(uniformLocation, value0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(string uniform, T value0, T value1) {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);

	switch (typeid(T)) {

		case typeid(double) :
			glUniform2d(uniformLocation, value0, value1);
			break;

		case typeid(float) :
			glUniform2f(uniformLocation, value0, value1);
			break;

		case typeid(int) :
			glUniform2i(uniformLocation, value0, value1);
			break;

		case typeid(uint) :
			glUniform2ui(uniformLocation, value0, value1);
			break;

	}

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(string uniform, T value0, T value1, T value2) {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);

	if (typeid(T) == typeid(double)) glUniform3d(uniformLocation, value0, value1, value2);
	else if (typeid(T) == typeid(float)) glUniform3f(uniformLocation, value0, value1, value2);
	else if (typeid(T) == typeid(int)) glUniform3i(uniformLocation, value0, value1, value2);
	else if (typeid(T) == typeid(uint)) glUniform3ui(uniformLocation, value0, value1, value2);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(string uniform, T value0, T value1, T value2, T value3) {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);

	switch (typeid(T)) {

		case typeid(double) :
			glUniform4d(uniformLocation, value0, value1, value2, value3);
			break;

		case typeid(float) :
			glUniform4f(uniformLocation, value0, value1, value2, value3);
			break;

		case typeid(int) :
			glUniform4i(uniformLocation, value0, value1, value2, value3);
			break;

		case typeid(uint) :
			glUniform4ui(uniformLocation, value0, value1, value2, value3);
			break;

	}

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform matrix
void Shader::setUniformMatrix(string uniform, float* value) {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value);

}

template <class T> void Shader::setUniformArray(string uniform, uint size, T* pointer) {

	if (uniform == "") return;
	GLuint uniformLocation = this->getUniformLocation(uniform);

	if (typeid(T) == typeid(double)) glUniform3dv(uniformLocation, size, (const GLdouble*)pointer);
	else if (typeid(T) == typeid(float)) glUniform3fv(uniformLocation, size, (const GLfloat*) pointer);
	else if (typeid(T) == typeid(int)) glUniform3iv(uniformLocation, size, (const GLint*) pointer);
	else if (typeid(T) == typeid(uint)) glUniform3uiv(uniformLocation, size, (const GLuint*) pointer);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Loads shader from a String and returns if success
bool Shader::loadFromStrings(string vertexShader, string fragmentShader) {

	// Support to vertex + fragment shader
	// Geometry shader not supported
	GLuint programId = glCreateProgram();
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;

	// Compile vertex Shader
	const char * vertexShaderPointer = vertexShader.c_str();
	glShaderSource(vertexShaderId, 1, &vertexShaderPointer, NULL);
	glCompileShader(vertexShaderId);

	#ifdef DEBUG
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
		Log::cout << "Vertex shader: " << (result ? "OK" : "ERROR") << endl;
	#endif

	// Compile fragment Shader
	const char * fragmentShaderPointer = fragmentShader.c_str();
	glShaderSource(fragmentShaderId, 1, &fragmentShaderPointer, NULL);
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
				GLint errorLength;
				glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &errorLength);
				string errorMessage(errorLength, 1);
				glGetProgramInfoLog(programId, errorLength, NULL, &errorMessage[0]);
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
bool Shader::loadFromFiles(string vertexShader, string fragmentShader) {

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

	return this->loadFromStrings(vertexShaderCode, fragmentShaderCode);

}