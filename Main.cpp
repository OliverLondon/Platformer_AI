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

	//make and run the game window
	sf::RenderWindow window(sf::VideoMode(704, 384), "AI Platformer", sf::Style::Close);
	window.setFramerateLimit(30);
	//
	//sf::Text t = sf::Text(sf::String("position is"+player.position);
	//
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {window.close();}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				player.Move_left();
				printf("%s\n", "Left key pressed!");
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				player.Move_right();
				printf("%s\n", "Right key pressed!");
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				printf("%s\n", "Space key pressed!");
				if (player.on_ground) {
					player.Jump();
				}
			}
		}
		float xx = player.position.x;
		float yy = player.position.y;
		///printf("Player position: %f %f\n",xx,yy);


		// clear the window with a color
		window.clear(sf::Color::White);
		
		// draw everything here...		
		map.DrawMap(window);
		player.Step(map,player);
		player.Draw(window);
		
		if (player.has_won) {//quit game if reach the end
			window.close();
		}
		if (player.hp <= 0) {//if the player has died
			window.close();
		}

		// end the current frame
		window.display();
	}
	
	return 0;
}
