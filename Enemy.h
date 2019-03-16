#pragma once
#include "Player.h"
class Enemy :
	public Player
{
public:
	Enemy();
	~Enemy();
	int hp = 10;
	int dmg = 1;

};

