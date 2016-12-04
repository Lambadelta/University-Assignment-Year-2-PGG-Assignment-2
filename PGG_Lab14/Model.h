#ifndef MODEL_H
#define MODEL_H

#include "Object.h"
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "Shader.h"
#include "PVector.h"
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_image.h>
/**
@brief A class that represents a Model
Contains all the methods, and variables to create a 3D model
*/
class Model
{
public:
	/**
	@brief The Default Constructor
	*/
	Model();
	/**
	@brief The Virtual Destructor
	*/
	virtual ~Model(){};
	/**
	@brief A method to draw the Model
	@param glm::mat4& - A matrix 4 containing a reference to the view Matrix
	@param glm::mat4& - A matrix 4 containing a reference to the projection Matrix
	*/
	void draw(glm::mat4&, glm::mat4&);
	/**
	@brief A method to update variables using a float
	@param float dt - A float containing deltatime
	*/
	virtual void update(float) = 0;
	/**
	@brief A method to load a in a texture using SDL
	It reads in the file, and returns a surface that
	OpenGL can use
	@param std::string - A string containing the path
	*/
	void loadTexture(std::string);
	/**
	@brief A method to initialise the VAO, and VBOs
	@param std::string - A string containing the file path for the Vertex Shader
	@param std::string - A string containing the file path for the Fragment Shader
	*/
	void initVAO(std::string, std::string);
	/**
	@brief A method to initialise the Texture
	@param std::string A strain containing the path
	*/
	void initTexture(std::string);
	/**
	@brief A method to update the position of the Model
	@param float xin - A float that contains a position
	@param float yin - A float that contains a position
	@param float zin - A float that contains a position 
	*/
	void setPosition(float xin, float yin, float zin)
	{
		Position.x = xin, Position.y = yin, Position.z = zin;
	};
	/**
	@brief A method to update the Object Mesh
	@param Object - An object containing the mesh data
	*/
	void setMeshObject(Object Mesh){ this->Mesh = Mesh; };
	/**
	@brief A method to set the rotation of the Model
	@param float xin - A float that contains a Rotation
	@param float yin - A float that contains a Rotation
	@param float zin - A float that contains a Rotation
	*/
	void setRotation(float xin, float yin, float zin){ Rotation.x = xin; Rotation.y = yin; Rotation.z = zin; };
	/**
	@brief A method to get the Shader
	@returns Shader - A Shader containing the shader
	*/
	Shader getShader(){ return shader; };
	/**
	@brief A method to get the Mesh
	@returns Object - A Object containing the mesh
	*/
	Object getMesh(){ return Mesh; };
	/**
	@brief A method to get A PVector of the Top left Point
	@returns PVector - A PVector containing the top left x + y
	*/
	PVector getXYPos(){ return PV; };

protected:
	///An object containing mesh
	Object Mesh;
	///A vec3 containing position
	glm::vec3 Position;
	///A vec3 containing rotation
	glm::vec3 Rotation;

	///The Model Matrix
	glm::mat4 ModelMatrix;

	///A Vertex Array Object
	GLuint VAO;
	///A Position Buffer
	GLuint positionBuffer;
	///A Normal buffer
	GLuint normalBuffer;
	///A Texture Buffer
	GLuint textureBuffer;
	///A location to texture coordinates
	GLuint textureCoord;
	///A shader used to create the Shader
	Shader shader;
	///A Shader Program
	GLuint Program;
	///Loations of the Shader
	GLuint 	_shaderModelMatLocation, _shaderViewMatLocation, _shaderProjMatLocation, _textureLocation;
	///A Attribute texture coordinate
	GLuint attribute_texcoord;
	///A point vector is the Top Left point
	PVector PV;
	///A pointer pointing to a surface to be used as a texture
	SDL_Surface* Texture;
	///Attribute name of a attribute
	GLchar* attribute_name;

	///Number of vertices
	unsigned int numVerts;
};

#endif