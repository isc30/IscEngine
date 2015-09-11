#pragma once

#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>

namespace IscEngine {

	class Window : public sf::RenderWindow {

		private:

			bool focus;

		public:
				
			Window(sf::VideoMode size, string title, unsigned int style, sf::ContextSettings contextSettings);

			void setFocus(bool focus) { this->focus = focus; }
			bool isFocused() { return this->focus; }

	};

};