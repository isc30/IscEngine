#ifndef SFMLOPENGL_H
#define SFMLOPENGL_H

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

void beginSfml(sf::RenderWindow* window) {

	window->pushGLStates();
	//window->resetGLStates();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void endSfml(sf::RenderWindow* window) {

	window->popGLStates();

}

#endif