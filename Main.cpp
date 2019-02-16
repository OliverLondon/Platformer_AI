using namespace std;
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "GameMap.h"
//#include "Enemy.h"
#include "Player.h"
#include <vector>

int main(int argc, char* argv[]) {
	//set the map
	GameMap map;
	map.SetMap(3);
	Player player;
	player.SetPos(map.GetStart());

	//Create the map's image storage
	int x = map.GetWidth();
	int y = map.GetHeight();
	int z = x * y;
	std::vector<sf::ConvexShape> boardImage(z);
	//set and color each tile
	map.FillMap(&boardImage);

	//make and run the game window
	sf::RenderWindow window(sf::VideoMode(512, 256), "AI Platformer", sf::Style::Close);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {window.close();}
		}

		// clear the window with a color
		window.clear(sf::Color::Red);
		
		// draw everything here...		
		for (int i = 0; i < z; i++) {
			window.draw(boardImage[i]);
		}

		// end the current frame
		window.display();
	}
	
	return 0;
}