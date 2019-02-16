#pragma once
#include "Physics.h"
#include <SFML/Graphics.hpp>
class Player :
	public Physics
{
public:
	Player();
	~Player();
	sf::RectangleShape icon;
	int hp = 50;
	int dmg = 5;

	sf::Vector2f position;
	void SetPos(sf::Vector2f);

	void Draw(sf::RenderWindow &window) const;

};

