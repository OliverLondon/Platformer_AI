#include <SFML/Graphics.hpp>
#pragma once
class Tiles
{
public:
	Tiles();
	~Tiles();

	void Air(sf::ConvexShape *, int x, int y);
	void Ground(sf::ConvexShape *, int x, int y);
	void LeftRamp(sf::ConvexShape *, int x, int y); //giong up
	void RightRamp(sf::ConvexShape *, int x, int y); //going down
	void Slab(sf::ConvexShape *, int x, int y);
	
	void ccc(sf::CircleShape *, int x);

	void convex_shape(sf::ConvexShape &, int top, int left, int right, int bottom);
	void flag(sf::ConvexShape &q, int top, int left, int right, int bottom);
};

