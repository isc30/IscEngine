#include "Buffer.hpp"
using namespace IscEngine;

Buffer::Buffer(vector<GLfloat> data, GLuint componentCount) {

	this->count = data.size();
	this->componentCount = componentCount;

	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

Buffer::~Buffer() {

	glDeleteBuffers(1, &this->id);

}

void Buffer::bind() {

	glBindBuffer(GL_ARRAY_BUFFER, this->id);

}

void Buffer::unbind() {

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}