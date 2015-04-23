#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include "Model.h"

class PlayerEntity : public Model
{
public:
	PlayerEntity();
	~PlayerEntity();

	void update(float);
	void setPosition(float xin, float yin, float zin)
	{ Position.x = xin, Position.y = yin, Position.z = zin; };
	void setMeshObject(Object Mesh){ this->Mesh = Mesh; };
	void movePLeft(bool b){ moveLeft = b; };
	void movePRight(bool b){ moveRight = b; };
	
private:

	bool moveLeft;
	bool moveRight;

	static float fPlayerSpeed;
	static float fRotateSpeed;
	static float fRotationMax;
};

#endif