#include "VertexArray.hpp"
using namespace IscEngine;

#include <iostream>
using namespace std;

VertexArray::VertexArray() {

	glGenVertexArrays(1, &this->id);

}

VertexArray::~VertexArray() {

	for (Buffer*& buffer : this->buffers) { delete buffer; buffer = nullptr; }
	glDeleteVertexArrays(1, &this->id);

}

void VertexArray::addBuffer(Buffer* const buffer, const unsigned int index) {

	VertexArray::bind(this);
	Buffer::bind(buffer);
	
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

	Buffer::unbind();
	VertexArray::unbind();

	this->buffers.push_back(buffer);

}

void VertexArray::bind(const VertexArray* const vertexArray) {

	glBindVertexArray(vertexArray->id);

}

void VertexArray::unbind() {

	glBindVertexArray(0);

}