#include "BackgroundPlane.h"

BackgroundPlane::BackgroundPlane()
{
	isAlive = true;
	spin = false;
}

BackgroundPlane::~BackgroundPlane()
{

}


void BackgroundPlane::update(float dt)
{
	if (spin)
	{
		Rotation.y += dt * 1.f;
		while (Rotation.y > (float)(3.1415 * 2.0))
		{
			Rotation.y -= (float)(3.1415 * 2.0);
		}
	}
	ModelMatrix = glm::translate(glm::mat4(1.0F), Position);
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.y, glm::vec3(0, 1, 0));
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.x, glm::vec3(1, 0, 0));
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.z, glm::vec3(0, 0, 1));
}
