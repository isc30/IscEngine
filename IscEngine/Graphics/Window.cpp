#include "Window.hpp"
using namespace IscEngine;

Window::Window(const sf::VideoMode& size, const string& title, const unsigned int style, const sf::ContextSettings& contextSettings) : sf::RenderWindow(size, title, style, contextSettings) {
	
	this->focus = true;

}

const bool Window::isFocused() const {

	return this->focus;

}

void Window::setFocus(const bool focus) {

	this->focus = focus;

}