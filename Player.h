#include "Physics.h"
#include "GameMap.h"
#include <SFML/Graphics.hpp>
#pragma once
class Player :
	public Physics
{
public:
	Player();
	~Player();

	int hp = 50;
	int dmg = 5;
	bool has_won = false;
	bool on_ground = false;

	sf::RectangleShape icon;
	sf::Vector2f position;
	void SetPos(sf::Vector2f);
	void MovePos(sf::Vector2f);
	void MovePos(float, float);

	void Move_left(void);
	void Move_right(void);
	void Jump(void);
	void Attack(void);

	void Step(GameMap &, Player &);

	void Draw(sf::RenderWindow &window) const;

};

