#include "PlayerEntity.h"

float PlayerEntity::fPlayerSpeed = 8.f;
float PlayerEntity::fRotateSpeed = 1.0f;
float PlayerEntity::fRotationMax = 0.5f;

PlayerEntity::PlayerEntity() : Model()
{
	VAO = 0;
	numVerts = 0;
	Lives = 3;
	moveLeft = moveRight = false;
	bTimer.setInitialTime(0.5f);
}

PlayerEntity::~PlayerEntity()
{
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &textureBuffer);
	SDL_FreeSurface(Texture);
}


void PlayerEntity::update(float dt)
{
	bTimer.updateTimer(dt);
	if (moveLeft)
	{
		if (Rotation.z > -fRotationMax)
		{
			Rotation.z -= fRotateSpeed *dt;
		}
		if (Position.x > -10.0f)
		{
			Position.x -= fPlayerSpeed *dt;
		}
	}
	if (moveRight)
	{
		if (Rotation.z < fRotationMax)
		{
			Rotation.z += fRotateSpeed *dt;
		}
		if (Position.x < 10.0f)
		{
			Position.x += fPlayerSpeed *dt;
		}
	}
	if ((!moveLeft && !moveRight) || (moveLeft && moveRight))
	{
		if (Rotation.z < 0.0f)
		{
			Rotation.z += (fRotateSpeed / 2) *dt;
		}
		if (Rotation.z > 0.0f)
		{
			Rotation.z -= (fRotateSpeed / 2) *dt;
		}
	}
	ModelMatrix = glm::translate(glm::mat4(1.0F), Position);
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.y, glm::vec3(0, 1, 0));
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.x, glm::vec3(1, 0, 0));
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.z, glm::vec3(0, 0, 1));
	for (int i = 0; i < vBullet.size(); i++)
	{
		vBullet[i].update(dt);
	}

	PV.x = Position.x - 1.5f;
	PV.y = Position.y - 2.5f;
}

void PlayerEntity::shootBullet()
{
	if (vBullet.size() <= 5)
	{
		if (bTimer.expiredTimer())
		{
			Bullet newBullet;
			newBullet.setMeshObject(bulletMesh);
			newBullet.initVAO("vShader.txt", "fShader.txt");
			newBullet.initTexture("PBulletTexture.png");
			newBullet.setPosition(Position.x, Position.y, Position.z);
			newBullet.setRotation(Rotation.x, Rotation.y, Rotation.z);
			vBullet.push_back(newBullet);
			bTimer.resetTimer();
		}
	}
	
}
