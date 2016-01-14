#pragma once

#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>

namespace IscEngine {

	class Window : public sf::RenderWindow {

		private:

			bool focus;

		public:
				
			Window(const sf::VideoMode& size, const string& title, const unsigned int style, const sf::ContextSettings& contextSettings);

			const bool isFocused() const;
			void setFocus(const bool focus);

	};

};