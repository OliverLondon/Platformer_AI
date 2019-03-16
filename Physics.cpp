#include "Physics.h"
#include "GameMap.h"
#include "Player.h"
using namespace std;
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

Physics::Physics()
{
	ax, ay, vx, vy = 0.f;
	g = 0.5f;
	f = 0.1f;
}


Physics::~Physics()
{
}


void Physics::Move(GameMap &m, Player &p) {
	//apply changes
	ay += g; //Apply gravity
	if (ax > 0.f) {//Apply friction
		ax -= f;
		if (ax < 0.f) {	ax = 0;	}//Don't twitch in place
	}
	else {
		ax += f;
		if (ax > 0.f) { ax = 0; }//Don't twitch in place
	}
	vx += ax;
	vy += ay;
	//cap speeds
	if (vx > 4.f) { vx = 4.f; }//max right speed
	if (vx < -4.f) { vx = -4.f; }//max left speed
	if (vy > 10.f) { vy = 10.f; }//max down speed
	if (vy < -6.f) { vy = -6.f; }//max up speed
	//update position
	p.MovePos(sf::Vector2f(vx, vy));

	//Collision
	sf::Rect<float> r = p.icon.getGlobalBounds();
	std::vector<sf::ConvexShape> tileSet = m.GetTiles();
	int numtiles = tileSet.size();
	//check if any tile on map overlaps the icon.
	for (int i = 0; i < numtiles; i++) {
		sf::Rect<float> temp = tileSet[i].getGlobalBounds();

		if (r.intersects(temp)) {//if so, get the bounds and see if player is touching the ground or a wall, or both.
			//check how the player hit the wall, and push them back in bounds. Also kills velocity in the direction the wall was hit.
			if ((temp.left == tileSet.back().getPoint(0).x) && (temp.top == tileSet.back().getPoint(0).y)) {//if thing touched is the goal flag
				p.has_won = true;
				break;
			}

			Collision(temp, p);
			r = p.icon.getGlobalBounds(); //update r
		}
	}



}

void Physics::Collision(sf::Rect<float> &touching, Player &p) {
	//vector is 2 sets of :tl, tr, br, bl
	///printf("Wall has walls at: %f, %f, %f, %f\n",touching.left , touching.top , touching.left + touching.width , touching.top + touching.height);
	std::vector<int> corners;// 0 = top left, 1 = top right, 2 = bottom right, 3 = bottomt left.
	for (int i = 0; i < 4; i++) {
		sf::Vector2f point = p.icon.getTransform().transformPoint(p.icon.getPoint(i));
		
		///printf("Checking point (%f, %f).\n", point.x, point.y);
		///printf(touching.contains(point) ? "point in rect!\n" : "point not in rect.\n");
		if (touching.contains(point)) {
			corners.emplace_back(i);
			///printf("Corner %d touching the player!\n", i);
		}
	}
	///printf("corners size = %d\n", corners.size());
	if (corners.size() == 0){
		return;
	}

	if (corners.size() > 1) {//Should only ever have 2 values in the list
		///printf("Here A!\n");
		///printf("The 2 corners are %d and %d\n", corners[0], corners[1]);
		sf::Vector2f p1 = p.icon.getTransform().transformPoint(p.icon.getPoint(corners[0]));
		sf::Vector2f p2 = p.icon.getTransform().transformPoint(p.icon.getPoint(corners[1]));
		///printf("And they have corrds of (%f, %f) and (%f, %f).\n",p1.x,p1.y,p2.x,p2.y);
		if (p1.x == p2.x) {//if a side is full colliding with the wall
			///printf("Here A1!\n");
			float dist_from_left = p1.x - touching.left;
			float dist_from_right = abs(p1.x - (touching.left + touching.width));
			if (dist_from_left > dist_from_right) {//if the left side of icon is touching right side of wall
				///printf("Here 1!\n");
				vx = 0;
				//push player back inbounds
				p.MovePos(dist_from_right + 0.01f, 0.f);//add a small padding value
			}
			else {//if the right side of icon is touching left side of wall
				///printf("Here 2!\n");
				vx = 0;
				//push player back inbounds
				p.MovePos(-(dist_from_left + 0.01f), 0.f);//add a small padding value
			}
		}
		else if (p1.y == p2.y) {// if full top/bottom is colliding with wall. If is implied if previous fails, but checking anyway.
			///printf("Here A2!\n");
			float dist_from_top = p1.y - touching.top;
			float dist_from_bot = abs(p1.y - (touching.top + touching.height));

			if (dist_from_top > dist_from_bot) {//if top of icon is colliding with bottom of wall
				///printf("Here 3!\n");
				vy = 0;
				//push player back inbounds
				p.MovePos(0.f, dist_from_bot + 0.01f); //bigger y means player is lower
			}
			else { //if bottom of icon is colliding with top of wall
				///printf("Here 4!\n");
				vy = 0;
				//push player back inbounds
				p.MovePos(0.f, -(dist_from_top + 0.01f)); //bigger y means player is lower
				p.on_ground = true;

			}
		}
	}
	else {
		/*
		check how the player hit the wall. Do this by comparing the dist to the nearest 2 sides of the wall that it could have passed through.
		for tl, this is the bottom and right wall.
		for tr, this is the bottom and left wall.
		for br, this is the top and left wall.
		for bl, this is the top and right wall.
		CORNER CASE: if the player hit a corner directly (within a set margin of 0.2) then both xv and vy are set to 0.
		*/		
		///printf("Here B!\n");
		sf::Vector2f point = p.icon.getTransform().transformPoint(p.icon.getPoint(corners[0]));
		float t_diff = point.y - (touching.top); //how far point is from the top of the wall
		float b_diff = (touching.top + touching.height) - point.y;//how far point is from the bottom of the wall
		float r_diff = (touching.left + touching.width) - point.x;//how far point is from the right of the wall
		float l_diff = point.x - (touching.left);//how far point is from the left of the wall
		
		if (t_diff < b_diff && t_diff < r_diff && t_diff < l_diff) {//if t_diff is smallest, it hit the top of the wall
			//push back up
			vy = 0.f;
			p.MovePos(0.f, -(t_diff + 0.01f));
		}
		else if (b_diff < t_diff && b_diff < r_diff && b_diff < l_diff) {//if b_diff is smallest, it hit the bottom of the wall
			//push back down
			vy = 0.f;
			p.MovePos(0.f, b_diff + 0.01f);
		}
		else if (r_diff < b_diff && r_diff < t_diff && r_diff < l_diff) {//if r_diff is smallest, it hit the right side of the wall
			//push to the right
			vx = 0.f;
			p.MovePos(r_diff + 0.01f, 0.f);
		}
		else {//if l_diff is smallest, it hit the left side of the wall
			//push to the left
			vx = 0.f;
			p.MovePos(-(l_diff + 0.01f), 0.f);
		}
	}
}
