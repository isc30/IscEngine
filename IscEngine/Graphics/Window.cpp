#include "Window.hpp"
using namespace IscEngine;

Window::Window(sf::VideoMode size, string title, unsigned int style, sf::ContextSettings contextSettings) : sf::RenderWindow(size, title, style, contextSettings) {
	
	this->focus = true;

}