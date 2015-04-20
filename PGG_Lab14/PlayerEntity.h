#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include "Model.h"

class PlayerEntity : protected Model
{
public:
	PlayerEntity();
	~PlayerEntity();

	void draw();
	void update();
	void initVAO();
	void setPosition(float xin, float yin, float zin)
	{ Position.x = xin, Position.y = yin, Position.z = zin; };
	
private:
};

#endif