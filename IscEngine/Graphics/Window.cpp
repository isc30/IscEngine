#include "Window.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
Window::Window(const sf::VideoMode& size, const string& title, const unsigned int style, const sf::ContextSettings& contextSettings) : sf::RenderWindow(size, title, style, contextSettings) {
	
	this->focus = true;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns if the Window is focused
bool Window::isFocused() const {

	return this->focus;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sets the focus status of the Window
void Window::setFocus(const bool focus) {

	this->focus = focus;

}