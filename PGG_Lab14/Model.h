#ifndef MODEL_H
#define MODEL_H
#include "Object.h"
#include "glew.h"
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "Shader.h"

class Model
{
public:
	Model();
	virtual ~Model(){};

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void initVAO() = 0;
	virtual void setPosition() = 0;

	Object getMesh(){ return Mesh; };


protected:
	Object Mesh;

	glm::vec3 Position;
	glm::vec3 Rotation;

	glm::mat4 ModelMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	GLuint VAO;
	Shader shader;

	unsigned int numVerts;
};

#endif