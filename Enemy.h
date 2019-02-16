#pragma once
#include "Physics.h"
class Enemy :
	public Physics
{
public:
	Enemy();
	~Enemy();
	int hp = 10;
	int dmg = 1;

};

