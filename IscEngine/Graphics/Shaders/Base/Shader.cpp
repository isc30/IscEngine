#include "Shader.hpp"
#include "../../../Utils/Log.hpp"
using namespace IscEngine;

// Initialize static variables
Shader* Shader::currentShader = nullptr;

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

	Log::cout << "Borrando shader " << this->id << endl;
	glDeleteProgram(this->id);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns the id
const unsigned int Shader::getId() const {

	return this->id;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Binds the shader
void Shader::bind() const {

	glUseProgram(this->id);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Unbinds the shader
void Shader::unbind() const {

	glUseProgram(0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns shader uniform location
const int Shader::getUniformLocation(const char* uniform) const {

	return glGetUniformLocation(this->id, uniform);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns shader attribute location
const int Shader::getAttributeLocation(const char* attribute) const {

	return glGetAttribLocation(this->id, attribute);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(const char* uniform, T value0) {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);
	
	if (typeid(T) == typeid(double)) glUniform1d(uniformLocation, value0);
	else if (typeid(T) == typeid(float)) glUniform1f(uniformLocation, value0);
	else if (typeid(T) == typeid(int)) glUniform1i(uniformLocation, value0);
	else if (typeid(T) == typeid(unsigned int)) glUniform1ui(uniformLocation, value0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(const char* uniform, T value0, T value1) {

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
template <class T> void Shader::setUniform(const char* uniform, T value0, T value1, T value2) {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);

	if (typeid(T) == typeid(double)) glUniform3d(uniformLocation, value0, value1, value2);
	else if (typeid(T) == typeid(float)) glUniform3f(uniformLocation, value0, value1, value2);
	else if (typeid(T) == typeid(int)) glUniform3i(uniformLocation, value0, value1, value2);
	else if (typeid(T) == typeid(unsigned int)) glUniform3ui(uniformLocation, value0, value1, value2);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a shader uniform value
template <class T> void Shader::setUniform(const char* uniform, T value0, T value1, T value2, T value3) {

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
void Shader::setUniformMatrix(const char* uniform, float* value) {

	if (uniform == "") return;
	int uniformLocation = this->getUniformLocation(uniform);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value);

}

template <class T> void Shader::setUniformArray(const char* uniform, uint size, T* pointer) {

	if (uniform == "") return;
	GLuint uniformLocation = this->getUniformLocation(uniform);

	if (typeid(T) == typeid(double)) glUniform3dv(uniformLocation, size, (const GLdouble*)pointer);
	else if (typeid(T) == typeid(float)) glUniform3fv(uniformLocation, size, (const GLfloat*) pointer);
	else if (typeid(T) == typeid(int)) glUniform3iv(uniformLocation, size, (const GLint*) pointer);
	else if (typeid(T) == typeid(unsigned int)) glUniform3uiv(uniformLocation, size, (const GLuint*) pointer);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Loads shader from a String and returns if success
const bool Shader::loadFromStrings(const char* vertexShader, const char* fragmentShader) {

	// Support to vertex + fragment shader
	// Geometry shader not supported
	GLuint programId = glCreateProgram();
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;

	// Compile vertex Shader
	glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
	glCompileShader(vertexShaderId);

	#ifdef DEBUG
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
		Log::cout << "Vertex shader: " << (result ? "OK" : "ERROR") << endl;
	#endif

	// Compile fragment Shader
	glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
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
const bool Shader::loadFromFiles(const string& vertexShader, const string& fragmentShader) {

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