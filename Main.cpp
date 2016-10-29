#include <iostream>
#include <thread>
using namespace std;

#include "IscEngine/Engine.hpp"
#include "IscEngine/Scenes/TestScene.hpp"
using namespace IscEngine;

///////////////////////////////////////////////////////////////////////////////
// https://github.com/isc30/IscEngine
int main()
{
	Engine game;
	game.create("Woo", 1920, 1080, sf::Style::Fullscreen);
	game.setScene(new Scenes::TestScene(game.getWindow()));
	game.run();

	return 0;
}