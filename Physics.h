using namespace std;
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameMap.h"
class Player;
#pragma once
class Physics
{
public:
	Physics();
	~Physics();

	float ax, ay, vx, vy, g, f;//movement vectors
	std::vector<float> pos;
	

	void Move(GameMap &, Player &p);
	
	void Collision(sf::Rect<float> &, Player &p);

};

