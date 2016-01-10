#include "Mesh.hpp"
#include "../Shaders/ShaderManager.hpp"
using namespace IscEngine;

Mesh::Mesh(vector<float> vertices) {

	this->vertexBuffer = new Buffer(vertices, 3);
	vertexArray = new VertexArray();
	int position = ShaderManager::currentShader->getAttributeLocation("vertexPosition_modelspace");
	vertexArray->addBuffer(this->vertexBuffer, position);

	this->indexBuffer = nullptr;
	this->normalBuffer = nullptr;
	this->textureBuffer = nullptr;
	this->colorBuffer = nullptr;

}

Mesh::Mesh(Buffer* vertexBuffer) {

	this->vertexBuffer = vertexBuffer;
	vertexArray = new VertexArray();
	int position = ShaderManager::currentShader->getAttributeLocation("vertexPosition_modelspace");
	vertexArray->addBuffer(this->vertexBuffer, position);

	this->indexBuffer = nullptr;
	this->normalBuffer = nullptr;
	this->textureBuffer = nullptr;
	this->colorBuffer = nullptr;

}

Mesh::~Mesh() {

	delete this->vertexArray;

}

void Mesh::addIndexes(vector<GLuint> indexes) {

	this->indexBuffer = new IndexBuffer(indexes);

}

void Mesh::addIndexBuffer(IndexBuffer* indexBuffer) {

	this->indexBuffer = indexBuffer;

}

void Mesh::addNormals(vector<float> normals) {

	this->normalBuffer = new Buffer(normals, 3);
	int position = ShaderManager::currentShader->getAttributeLocation("vertexNormal_modelspace");
	vertexArray->addBuffer(this->normalBuffer, position);

}

void Mesh::addNormalBuffer(Buffer* normalBuffer) {

	this->normalBuffer = normalBuffer;
	int position = ShaderManager::currentShader->getAttributeLocation("vertexNormal_modelspace");
	vertexArray->addBuffer(this->normalBuffer, position);

}

void Mesh::addTextureCoords(vector<float> textureCoords) {

	this->textureBuffer = new Buffer(textureCoords, 2);
	int position = ShaderManager::currentShader->getAttributeLocation("vertexUV");
	vertexArray->addBuffer(this->textureBuffer, position);

}

void Mesh::addTextureBuffer(Buffer* textureBuffer) {

	this->textureBuffer = textureBuffer;
	int position = ShaderManager::currentShader->getAttributeLocation("vertexUV");
	vertexArray->addBuffer(this->textureBuffer, position);

}

void Mesh::addColors(vector<float> colors) {

	this->colorBuffer = new Buffer(colors, 3);
	int position = ShaderManager::currentShader->getAttributeLocation("vertexColor");
	vertexArray->addBuffer(this->colorBuffer, position);

}

void Mesh::addColorBuffer(Buffer* colorBuffer) {

	this->colorBuffer = colorBuffer;
	int position = ShaderManager::currentShader->getAttributeLocation("vertexColor");
	vertexArray->addBuffer(this->colorBuffer, position);

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