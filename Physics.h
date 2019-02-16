

#pragma once
class Physics
{
public:
	Physics();
	~Physics();
	float ax, ay, x, y, g;//movement vectors
	std::vector<float> pos;
private:
	void Move(float x, float y, float ax, float ay);


};

