#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include "Model.h"

class PlayerEntity : public Model
{
public:
	PlayerEntity();
	~PlayerEntity();

	void draw(glm::mat4&, glm::mat4&);
	void update(float);
	void initVAO();
	void setPosition(float xin, float yin, float zin)
	{ Position.x = xin, Position.y = yin, Position.z = zin; };
	void setMeshObject(Object Mesh){ this->Mesh = Mesh; };
	
private:
};

#endif