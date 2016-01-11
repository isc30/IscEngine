#include "Mesh.hpp"
#include "../Shaders/ShaderManager.hpp"
#include "../../Utils/Log.hpp"
using namespace IscEngine;

Mesh::Mesh(vector<float> vertices) {

	this->vertexBuffer = new Buffer(vertices, 3);
	this->indexBuffer = nullptr;
	this->normalBuffer = nullptr;
	this->textureBuffer = nullptr;
	this->colorBuffer = nullptr;

}

Mesh::Mesh(Buffer* vertexBuffer) {

	this->vertexBuffer = vertexBuffer;
	this->indexBuffer = nullptr;
	this->normalBuffer = nullptr;
	this->textureBuffer = nullptr;
	this->colorBuffer = nullptr;

}

Mesh::~Mesh() {

	this->vertexArrays.clear();

}

void Mesh::addIndexes(vector<unsigned int> indexes) {

	this->indexBuffer = new IndexBuffer(indexes);

}

void Mesh::addIndexBuffer(IndexBuffer* indexBuffer) {

	this->indexBuffer = indexBuffer;

}

void Mesh::addNormals(vector<float> normals) {

	this->normalBuffer = new Buffer(normals, 3);

}

void Mesh::addNormalBuffer(Buffer* normalBuffer) {

	this->normalBuffer = normalBuffer;

}

void Mesh::addTextureCoords(vector<float> textureCoords) {

	this->textureBuffer = new Buffer(textureCoords, 2);

}

void Mesh::addTextureBuffer(Buffer* textureBuffer) {

	this->textureBuffer = textureBuffer;

}

void Mesh::addColors(vector<float> colors) {

	this->colorBuffer = new Buffer(colors, 3);

}

void Mesh::addColorBuffer(Buffer* colorBuffer) {

	this->colorBuffer = colorBuffer;

}

void Mesh::render(GLenum type) {

	Shader* currentShader = ShaderManager::currentShader;

	if (GLEW_ARB_vertex_array_object) {
		
		VertexArray* currentVertexArray;

		if (this->vertexArrays.find(currentShader) == this->vertexArrays.end()) {

			Log::cout << "Creating VAO " << currentShader->getId() << std::endl;

			currentVertexArray = new VertexArray();
			currentVertexArray->addBuffer(this->vertexBuffer, currentShader->getAttributeLocation("vertexPosition_modelspace"));
			currentVertexArray->addBuffer(this->textureBuffer, currentShader->getAttributeLocation("vertexUV"));
			currentVertexArray->addBuffer(this->normalBuffer, currentShader->getAttributeLocation("vertexNormal_modelspace"));

			vertexArrays[currentShader] = currentVertexArray;

		} else {
			currentVertexArray = vertexArrays[currentShader];
		}

		// Render

		currentVertexArray->bind();

		if (this->indexBuffer != nullptr) {
			this->indexBuffer->bind();
			glDrawElements(type, this->vertexBuffer->getCount(), GL_UNSIGNED_INT, 0);
			this->indexBuffer->unbind();
		} else {
			glDrawArrays(type, 0, this->vertexBuffer->getCount());
		}

		currentVertexArray->unbind();

	} else {

		GLuint attributeLocation[3];
		attributeLocation[0] = currentShader->getAttributeLocation("vertexPosition_modelspace");
		glEnableVertexAttribArray(attributeLocation[0]);
		this->vertexBuffer->bind();
		glVertexAttribPointer(
			attributeLocation[0],  // The attribute we want to configure
			this->vertexBuffer->getComponentCount(),                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);
		this->vertexBuffer->unbind();

		attributeLocation[1] = currentShader->getAttributeLocation("vertexUV");
		glEnableVertexAttribArray(attributeLocation[1]);
		this->textureBuffer->bind();
		glVertexAttribPointer(
			attributeLocation[1],  // The attribute we want to configure
			this->textureBuffer->getComponentCount(),                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);
		this->textureBuffer->unbind();

		attributeLocation[2] = currentShader->getAttributeLocation("vertexNormal_modelspace");
		glEnableVertexAttribArray(attributeLocation[2]);
		this->normalBuffer->bind();
		glVertexAttribPointer(
			attributeLocation[2],  // The attribute we want to configure
			this->normalBuffer->getComponentCount(),                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);
		this->normalBuffer->unbind();

		if (this->indexBuffer != nullptr) {
			this->indexBuffer->bind();
			glDrawElements(type, this->vertexBuffer->getCount(), GL_UNSIGNED_INT, 0);
			this->indexBuffer->unbind();
		} else {
			glDrawArrays(type, 0, this->vertexBuffer->getCount());
		}

		glDisableVertexAttribArray(attributeLocation[0]);
		glDisableVertexAttribArray(attributeLocation[1]);
		glDisableVertexAttribArray(attributeLocation[2]);

	}

}