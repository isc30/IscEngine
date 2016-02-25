#include "Texture.hpp"
using namespace IscEngine;

void Texture::bind(const Texture* const texture, const unsigned int index, unsigned int type) {

	glActiveTexture(GL_TEXTURE0 + index);
	if (!glIsEnabled(type)) glEnable(type);
	glBindTexture(type, texture->id);

}

void Texture::unbind(const unsigned int index, unsigned int type) {
	
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(type, 0);
	if (glIsEnabled(type)) glDisable(type);

}

Texture::Texture() {

	this->id = 0;

}

Texture::~Texture() {

	glDeleteTextures(1, &this->id);

}

bool Texture::loadFromFile(const string& fileName) {

	sf::Image image;
	if (!image.loadFromFile(fileName)) return false;

	glGenTextures(1, &this->id);

	Texture::bind(this);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	Texture::unbind();

	this->width = image.getSize().x;
	this->height = image.getSize().y;

	return true;

}

bool Texture::loadCubeMap(const vector<string>& fileNames) {

	// http://learnopengl.com/#!Advanced-OpenGL/Cubemaps

	glGenTextures(1, &this->id);
	Texture::bind(this, 0, GL_TEXTURE_CUBE_MAP);

	sf::Image image;
	for (unsigned int i = 0, size = fileNames.size(); i < size; i++) {

		if (!image.loadFromFile(fileNames.at(i))) return false;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	Texture::unbind(0, GL_TEXTURE_CUBE_MAP);

	return true;

}

void Texture::create(const unsigned int width, const unsigned int height, const bool color, const bool depth) {

	glGenTextures(1, &this->id);
	Texture::bind(this);

	if (color) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	else if (depth) glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	if (color) {
		// Poor filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	if (depth) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	}

	if (!color) {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	this->width = width;
	this->height = height;

	Texture::unbind();

}