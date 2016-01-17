#include <iostream>
#include <thread>
using namespace std;

#include "IscEngine/Engine.hpp"
#include "IscEngine/Scenes/TestScene.hpp"
using namespace IscEngine;

///////////////////////////////////////////////////////////////////////////////
// https://github.com/isc30/IscEngine
int main() {

	Engine game;
	game.create("Woo", 800, 600, sf::Style::Close);
	game.setScene( new Scenes::TestScene( game.getWindow() ) );
	game.run();

	return 0;

}