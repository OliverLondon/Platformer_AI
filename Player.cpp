#include "Player.h"



Player::Player()
{
	icon = sf::RectangleShape(sf::Vector2f(20.f, 40.f));
	icon.setFillColor(sf::Color::Black);
}


Player::~Player()
{
}

void Player::Move_left(void) {
	ax = -0.4f;
}	

void Player::Move_right(void) {

	ax = 0.4f;
}

void Player::Jump(void) {
	if (on_ground) {
		ay = -6.f;
		on_ground = false;
	}
}

void Player::Attack(void) {

}

void Player::Step(GameMap &m, Player &p) {
	Move(m,p);
}

void Player::Draw(sf::RenderWindow &window) const {
	window.draw(icon);
}

void Player::SetPos(sf::Vector2f v) {
	position = {v};
	icon.setPosition(v);
}

void Player::MovePos(sf::Vector2f v) {
	icon.move(v);
	position += v;
}

void Player::MovePos(float x, float y) {
	icon.move(x,y);
	position += sf::Vector2f(x, y);
}

