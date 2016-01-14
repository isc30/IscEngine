#include "IndexBuffer.hpp"
using namespace IscEngine;

IndexBuffer::IndexBuffer(const vector<unsigned short>& data) {

	this->count = data.size();
	this->type = GL_UNSIGNED_SHORT;

	glGenBuffers(1, &this->id);
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned short), &data[0], GL_STATIC_DRAW);
	this->unbind();

}

IndexBuffer::IndexBuffer(const vector<unsigned int>& data) {

	this->count = data.size();
	this->type = GL_UNSIGNED_INT;

	glGenBuffers(1, &this->id);
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
	this->unbind();

}

IndexBuffer::~IndexBuffer() {

	glDeleteBuffers(1, &this->id);

}

const unsigned int IndexBuffer::getCount() const {
	
	return this->count;

}

const unsigned int IndexBuffer::getType() const {
	
	return this->type;

}

void IndexBuffer::bind() const {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

}

void IndexBuffer::unbind() const {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}