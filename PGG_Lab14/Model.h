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

	void draw(glm::mat4&, glm::mat4&);
	virtual void update(float) = 0;
	void initVAO(std::string, std::string);
	virtual void setPosition(float, float, float) = 0;
	void setRotation(float xin, float yin, float zin){ Rotation.x = xin; Rotation.y = yin; Rotation.z = zin; };
	Shader getShader(){ return shader; };
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
	GLuint Program;
	GLuint 	_shaderModelMatLocation, _shaderViewMatLocation, _shaderProjMatLocation;

	unsigned int numVerts;
};

#endif