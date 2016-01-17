#include "IndexBuffer.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////////////////////////////
// Binds the IndexBuffer
void IndexBuffer::bind(const IndexBuffer* const indexBuffer) {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->id);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Unbinds the IndexBuffer
void IndexBuffer::unbind() {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
IndexBuffer::IndexBuffer(const vector<unsigned short>& data) {

	this->size = data.size();
	this->type = GL_UNSIGNED_SHORT;

	glGenBuffers(1, &this->id);
	IndexBuffer::bind(this);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned short), &data[0], GL_STATIC_DRAW);
	IndexBuffer::unbind();

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
IndexBuffer::IndexBuffer(const vector<unsigned int>& data) {

	this->size = data.size();
	this->type = GL_UNSIGNED_INT;

	glGenBuffers(1, &this->id);
	IndexBuffer::bind(this);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
	IndexBuffer::unbind();

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
IndexBuffer::~IndexBuffer() {

	glDeleteBuffers(1, &this->id);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns the size
unsigned int IndexBuffer::getSize() const {
	
	return this->size;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns the type
unsigned int IndexBuffer::getType() const {
	
	return this->type;

}