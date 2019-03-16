#include "Tiles.h"
#include <SFML/Graphics.hpp>
//#include <Windows.h>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>

Tiles::Tiles()
{
}

Tiles::~Tiles()
{
}

void Tiles::Air(sf::ConvexShape *q, int y, int x) {
	(*q).setPointCount(4);
	(*q).setPoint(0, sf::Vector2f(0.f  + x * 32, 0.f  + y * 32));//top left
	(*q).setPoint(1, sf::Vector2f(32.f + x * 32, 0.f  + y * 32));//top right
	(*q).setPoint(2, sf::Vector2f(32.f + x * 32, 32.f + y * 32));//bottom right
	(*q).setPoint(3, sf::Vector2f(0.f  + x * 32, 32.f + y * 32));//bottom left
	(*q).setFillColor(sf::Color::White);
};

void Tiles::Ground(sf::ConvexShape *q, int y, int x) {
	(*q).setPointCount(4);
	(*q).setPoint(0, sf::Vector2f(0.f + x  * 32, 0.f  + y * 32));//top left
	(*q).setPoint(1, sf::Vector2f(32.f + x * 32, 0.f  + y * 32));//top right
	(*q).setPoint(2, sf::Vector2f(32.f + x * 32, 32.f + y * 32));//bottom right
	(*q).setPoint(3, sf::Vector2f(0.f + x  * 32, 32.f + y * 32));//bottom left
	(*q).setFillColor(sf::Color::Green);
};

void Tiles::LeftRamp(sf::ConvexShape *lr, int y, int x) {//going up
	(*lr).setPointCount(3);
	(*lr).setPoint(0, sf::Vector2f(0.f  + x * 32, 32.f + y * 32));//bottom left
	(*lr).setPoint(1, sf::Vector2f(32.f + x * 32, 32.f + y * 32));//bottom right
	(*lr).setPoint(2, sf::Vector2f(32.f + x * 32, 0.f  + y * 32));//top right
	(*lr).setFillColor(sf::Color::Green);
};

void Tiles::RightRamp(sf::ConvexShape *rr, int y, int x) {//going down
	(*rr).setPointCount(3);
	(*rr).setPoint(0, sf::Vector2f(0.f  + x * 32, 32.f + y * 32));//bottom left
	(*rr).setPoint(1, sf::Vector2f(32.f + x * 32, 32.f + y * 32));//bottom right
	(*rr).setPoint(2, sf::Vector2f(0.f  + x * 32, 32.f + y * 32));//top left
	(*rr).setFillColor(sf::Color::Green);
};

void Tiles::Slab(sf::ConvexShape *s, int y, int x) {
	(*s).setPointCount(4);
	(*s).setPoint(0, sf::Vector2f(0.f +  x * 32, 16.f + y * 32));//top left
	(*s).setPoint(1, sf::Vector2f(32.f + x * 32, 16.f + y * 32));//top right
	(*s).setPoint(2, sf::Vector2f(32.f + x * 32, 32.f + y * 32));//bottom right
	(*s).setPoint(3, sf::Vector2f(0.f +  x * 32, 32.f + y * 32));//bottom left
	(*s).setFillColor(sf::Color::Green);
};


void Tiles::ccc(sf::CircleShape *s, int x) {
	(*s).setRadius(x);
	(*s).setFillColor(sf::Color::Blue);
}

void Tiles::convex_shape(sf::ConvexShape &q, int top, int left, int right, int bottom) {
	/*
	top = top of row x
	left = left of column x
	right = right of column x
	bottom = bottom of row x
	*/
	q.setPointCount(4);
	q.setPoint(0, sf::Vector2f(0.f + left * 32, 0.f + top * 32));//top left
	q.setPoint(1, sf::Vector2f(32.f + right * 32, 0.f + top * 32));//top right
	q.setPoint(2, sf::Vector2f(32.f + right * 32, 32.f + bottom * 32));//bottom right
	q.setPoint(3, sf::Vector2f(0.f + left * 32, 32.f + bottom * 32));//bottom left
}

void Tiles::flag(sf::ConvexShape &q, int top, int left, int right, int bottom) {
	q.setPointCount(4);
	q.setPoint(0, sf::Vector2f(10.f + left * 32, 0.f + top * 32));//top left
	q.setPoint(1, sf::Vector2f(20.f + right * 32, 0.f + top * 32));//top right
	q.setPoint(2, sf::Vector2f(20.f + right * 32, 32.f + bottom * 32));//bottom right
	q.setPoint(3, sf::Vector2f(10.f + left * 32, 32.f + bottom * 32));//bottom left
	q.setFillColor(sf::Color(255, 255, 51));
}
