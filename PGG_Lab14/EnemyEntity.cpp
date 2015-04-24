#include "EnemyEntity.h"

float EnemyEntity::fVelocity = 2.5f;

float EnemyEntity::fRotationMax = 0.5f;;

EnemyEntity::EnemyEntity()
{
	isAlive = true;
	Shoot.setInitialTime(2.f);
}

EnemyEntity::~EnemyEntity()
{
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &textureBuffer);
}

void EnemyEntity::update(float dt)
{
	if (isAlive)
	{
		Shoot.updateTimer(dt);
		Position.y -= fVelocity * dt;
		if (Position.y <= -2.f)
		{ 
			if (!exitLeftorRight)
			{
				Position.x += fVelocity * 2 * dt;
				if (Rotation.z < fRotationMax)
				{
					Rotation.z += 1.0f * dt;
				}
			}
			else if (exitLeftorRight)
			{
				Position.x -= fVelocity * 2 * dt;
				if (Rotation.z > -fRotationMax)
				{
					Rotation.z -= 1.0f * dt;
				}
			}
		}
	}
	ModelMatrix = glm::translate(glm::mat4(1.0F), Position);
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.y, glm::vec3(0, 1, 0));
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.x, glm::vec3(1, 0, 0));
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.z, glm::vec3(0, 0, 1));
	PV.x = Position.x - 4.5f;
	PV.y = Position.y - 2.5f;
	shootBullet();
	for (int i = 0; i < vBullet.size(); i++)
	{
		vBullet[i].update(dt);
	}

	if ((Position.x <= -15.f) || (Position.x >= 15.f))
	{
		isAlive = false;
	}
}


void EnemyEntity::shootBullet()
{
	if (Shoot.expiredTimer())
	{
		if (vBullet.size() <= 0)
		{
			Bullet newBullet;
			newBullet.setMeshObject(bulletMesh);
			newBullet.initVAO("vShader.txt", "fShader.txt");
			newBullet.initTexture("EBulletTexture.png");
			newBullet.setPosition(Position.x, Position.y, Position.z);
			newBullet.setRotation(Rotation.x, Rotation.y, Rotation.z);
			newBullet.upordown(false);
			vBullet.push_back(newBullet);
			Shoot.resetTimer();
		}
	}
}
