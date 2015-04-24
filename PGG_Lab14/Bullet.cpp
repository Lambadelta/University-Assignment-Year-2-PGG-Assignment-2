#include "Bullet.h"

float Bullet::fVelocity = 9.0f;

Bullet::Bullet()
{
	UporDown = true;
}

Bullet::~Bullet()
{
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &textureBuffer);

}

void Bullet::update(float dt)
{
	if (isAlive)
	{
		if (UporDown)
		{
			Position.y += fVelocity * dt;
		}
		if (!UporDown)
		{
			Position.y -= fVelocity * dt;
		}
	}
	ModelMatrix = glm::translate(glm::mat4(1.0F), Position);
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.y, glm::vec3(0, 1, 0));
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.x, glm::vec3(1, 0, 0));
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.z, glm::vec3(0, 0, 1));
	PV.x = Position.x - 0.01f;
	PV.y = Position.y - 0.01f;
	if (Position.y >= 20.f || Position.y <= -20.f)
	{
		isAlive = false;
	}
}
