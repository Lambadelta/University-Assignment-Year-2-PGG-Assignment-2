#include "PlayerEntity.h"

float PlayerEntity::fPlayerSpeed = 8.f;
float PlayerEntity::fRotateSpeed = 1.0f;
float PlayerEntity::fRotationMax = 0.5f;

PlayerEntity::PlayerEntity() : Model()
{
	VAO = 0;
	numVerts = 0;
	moveLeft = moveRight = false;
}

PlayerEntity::~PlayerEntity()
{

}


void PlayerEntity::update(float dt)
{
	if (moveLeft)
	{
		if (Rotation.z > -fRotationMax)
		{
			Rotation.z -= fRotateSpeed *dt;
		}
		Position.x -= fPlayerSpeed *dt;
	}
	if (moveRight)
	{
		if (Rotation.z < fRotationMax)
		{
			Rotation.z += fRotateSpeed *dt;
		}
		Position.x += fPlayerSpeed *dt;
	}
	if (!moveLeft && !moveRight)
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
}
