#include "Buffer.hpp"
using namespace IscEngine;

Buffer::Buffer(vector<float> data, unsigned int componentCount) {

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

void Buffer::bind() {

	glBindBuffer(GL_ARRAY_BUFFER, this->id);

}

void Buffer::unbind() {

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}