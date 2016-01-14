#include "Buffer.hpp"
using namespace IscEngine;

Buffer::Buffer(const vector<float>& data, const unsigned int componentCount) {

	this->count = data.size();
	this->componentCount = componentCount;

	glGenBuffers(1, &this->id);

	this->bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	this->unbind();

}

Buffer::~Buffer() {

	glDeleteBuffers(1, &this->id);

}

const unsigned int Buffer::getCount() const {

	return this->count;

}

const unsigned int Buffer::getComponentCount() const {

	return this->componentCount;

}

void Buffer::bind() const {

	glBindBuffer(GL_ARRAY_BUFFER, this->id);

}

void Buffer::unbind() const {

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}