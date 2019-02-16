#include "Player.h"



Player::Player()
{
	icon = sf::RectangleShape(sf::Vector2f(30.f, 60.f));
	icon.setFillColor(sf::Color::Cyan);
}


Player::~Player()
{
}

void Player::Draw(sf::RenderWindow &window) const {
	window.draw(icon);
}

void Player::SetPos(sf::Vector2f v) {
	position = {v};
}

