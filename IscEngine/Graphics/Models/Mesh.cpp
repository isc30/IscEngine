#include "Mesh.hpp"
using namespace IscEngine;

Mesh::Mesh(vector<float> vertices) {

	this->vertexBuffer = new Buffer(vertices, 3);
	vertexArray = new VertexArray();
	vertexArray->addBuffer(this->vertexBuffer, 0);

	this->indexBuffer = nullptr;
	this->normalBuffer = nullptr;
	this->textureBuffer = nullptr;
	this->colorBuffer = nullptr;

}

Mesh::Mesh(Buffer* vertexBuffer) {

	this->vertexBuffer = vertexBuffer;
	vertexArray = new VertexArray();
	vertexArray->addBuffer(this->vertexBuffer, 0);

	this->indexBuffer = nullptr;
	this->normalBuffer = nullptr;
	this->textureBuffer = nullptr;
	this->colorBuffer = nullptr;

}

Mesh::~Mesh() {

	delete this->vertexArray;

}

void Mesh::addIndexes(vector<GLushort> indexes) {

	this->indexBuffer = new IndexBuffer(indexes);
	vertexArray->addBuffer(this->normalBuffer, 1);

}

void Mesh::addIndexes(vector<GLuint> indexes) {

	this->indexBuffer = new IndexBuffer(indexes);

}

void Mesh::addIndexBuffer(IndexBuffer* indexBuffer) {

	this->indexBuffer = indexBuffer;

}

void Mesh::addNormals(vector<float> normals) {

	this->normalBuffer = new Buffer(normals, 3);
	vertexArray->addBuffer(this->normalBuffer, 1);

}

void Mesh::addNormalBuffer(Buffer* normalBuffer) {

	this->normalBuffer = normalBuffer;
	vertexArray->addBuffer(this->normalBuffer, 1);

}

void Mesh::addTextureCoords(vector<float> textureCoords) {

	this->textureBuffer = new Buffer(textureCoords, 2);
	vertexArray->addBuffer(this->textureBuffer, 2);

}

void Mesh::addTextureBuffer(Buffer* textureBuffer) {

	this->textureBuffer = textureBuffer;
	vertexArray->addBuffer(this->textureBuffer, 2);

}

void Mesh::addColors(vector<float> colors) {

	this->colorBuffer = new Buffer(colors, 3);
	vertexArray->addBuffer(this->colorBuffer, 3);

}

void Mesh::addColorBuffer(Buffer* colorBuffer) {

	this->colorBuffer = colorBuffer;
	vertexArray->addBuffer(this->colorBuffer, 3);

}

void Mesh::render(GLenum type) {

	this->vertexArray->bind();
	
	if (this->indexBuffer != nullptr) {

		this->indexBuffer->bind();
		glDrawElements(type, this->vertexBuffer->getCount(), GL_UNSIGNED_INT, 0);
		this->indexBuffer->unbind();

	} else {

		glDrawArrays(type, 0, this->vertexBuffer->getCount());

	}

	this->vertexArray->unbind();

}