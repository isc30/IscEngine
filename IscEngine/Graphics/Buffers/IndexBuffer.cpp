#include "IndexBuffer.hpp"
using namespace IscEngine;

IndexBuffer::IndexBuffer(vector<GLushort> data) {

	this->count = data.size();

	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

IndexBuffer::IndexBuffer(vector<GLuint> data) {

	this->count = data.size();

	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

IndexBuffer::~IndexBuffer() {

	glDeleteBuffers(1, &this->id);

}

void IndexBuffer::bind() {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

}

void IndexBuffer::unbind() {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}