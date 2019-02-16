#include "Physics.h"
using namespace std;
#include <vector>


Physics::Physics()
{
	g = 1;
	ax, ay, x, y = 0;

}


Physics::~Physics()
{
}


void Physics::Move(float x, float y, float ax, float ay) {
	//apply changes
	x += ax;
	y += ay;
	y -= g;
	//cap speeds
	if (x > 5) { x = 5; }
	if (y > 5) { y = 5; }
	

}
