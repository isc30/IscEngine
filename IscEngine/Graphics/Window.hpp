#pragma once

#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>

namespace IscEngine {

	// sf::RenderWindow extended
	class Window : public sf::RenderWindow {

		private:

			bool focus;

		public:
			
			// Creates the Window
			Window(const sf::VideoMode& size, const string& title, const unsigned int style, const sf::ContextSettings& contextSettings);

			// Returns if the Window is focused
			bool isFocused() const;
			// Sets the focus status of the Window
			void setFocus(const bool focus);

	};

};