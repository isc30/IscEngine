#include <iostream>
#include <thread>
using namespace std;

#include "IscEngine/Engine.hpp"
#include "IscEngine/Scenes/TestScene.hpp"
using namespace IscEngine;

///////////////////////////////////////////////////////////////////////////////
// Hola xD
int main() {

	Engine game;
	game.create("Woo", 640, 480, sf::Style::Close);
	game.setScene(new Scenes::TestScene(game.getWindow()));
	game.run();

	return 0;

}