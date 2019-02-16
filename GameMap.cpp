using namespace std;
#include "GameMap.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Tiles.h"
#include <vector>
/*
The corresponding id numbers:
0 = air
1 = square tile
2 = ramp tile going up
3 = ramp tile going down
4 = slab
*/

GameMap::GameMap()
{
	currentMapNumber = 0;

	world_1.reserve(9);//small flat
	world_1 =
	{
		0,0,0,
		0,0,0,
		1,1,1
	};

	world_2.reserve(20 * 3);//long flat
	world_2 =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	world_3.reserve(10 * 5);//walls
	world_3 = 
	{
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,1,0,0,0,1,0,0,0,
		0,0,1,0,0,0,1,0,0,0,
		1,1,1,1,1,1,1,1,1,1
	};
}


GameMap::~GameMap()
{
}


void GameMap::SetMap(int m) {
	currentMapNumber = m;
	switch (m) {
		case 1:
			currentMap = world_1;
			width = 3;
			height = 3;
			start = {0.f, 0.f};
			end = {2.f * 32, 0.f};
			break;
		case 2:
			currentMap = world_2;
			width = 20;
			height = 3;
			start = {0.f, 0.f};
			end = {19.f * 32, 0.f};
			break;
		case 3:
			currentMap = world_3;
			width = 10;
			height = 5;
			start = {0.f, 2.f * 32};
			end = {9.f * 32, 2.f * 32};
			break;
		default:
			currentMap = world_1;
			width = 3;
			height = 3;
			start = {0.f, 0.f};
			end = {2.f * 32, 0.f};
			break;
	}
}

std::vector<int> GameMap::GetMap() {
	return currentMap;
}

int GameMap::GetHeight() {
	return height;
}

int GameMap::GetWidth() {
	return width;
}

sf::Vector2f GameMap::GetStart() {
	return start;
}

sf::Vector2f GameMap::GetEnd() {
	return end;
}


void GameMap::FillMap(std::vector<sf::ConvexShape> *boardImage) {
	
	int row, col, z, tilenumber;
	z = width * height;
	for (int i = 0; i < z; i++) {
		row = i / width;
		col = i % width;

		tilenumber = currentMap[i];//get the tile number for that spot
		sf::ConvexShape *CS = &(*boardImage)[i];//make and pass a refrence to the current image tile
		//printf("%s %d\n", "tile type:", tilenumber);
		switch (tilenumber)//based on the number, make it a different shape
		{
		case 0:
			Air(CS, row, col);
			break;
		case 1:
			Ground(CS, row, col);
			break;
		case 2:
			LeftRamp(CS, row, col);
			break;
		case 3:
			RightRamp(CS, row, col);
			break;
		case 4:
			Slab(CS, row, col);
			break;
		default:
			break;
		}
	}
}