#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H
#include "Model.h"

class EnemyEntity : public Model
{
public:
	EnemyEntity();
	~EnemyEntity();

	void update(float);
	void setPosition(float xin, float yin, float zin)
	{
		Position.x = xin, Position.y = yin, Position.z = zin;
	};
	void setMeshObject(Object Mesh){ this->Mesh = Mesh; };
	void movePLeft(bool b){ moveLeft = b; };
	void movePRight(bool b){ moveRight = b; };

private:

	bool moveLeft;
	bool moveRight;

	static float fVelocity;
};

#endif