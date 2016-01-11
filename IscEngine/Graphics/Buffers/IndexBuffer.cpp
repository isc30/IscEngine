#include "IndexBuffer.hpp"
using namespace IscEngine;

IndexBuffer::IndexBuffer(vector<unsigned short> data) {

	this->count = data.size();

	glGenBuffers(1, &this->id);
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned short), &data[0], GL_STATIC_DRAW);
	this->unbind();

}

IndexBuffer::IndexBuffer(vector<unsigned int> data) {

	this->count = data.size();

	glGenBuffers(1, &this->id);
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
	this->unbind();

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