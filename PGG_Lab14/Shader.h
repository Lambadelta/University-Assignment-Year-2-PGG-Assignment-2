#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
/**
@brief A class that represents a shader

This class is used to create, and initalise the OpenGL shaders
*/
class Shader
{
public:
	/**
	@brief The Default Constructor
	*/
	Shader();
	/**
	@brief The Default Destructor
	*/
	~Shader();
	/**
	@brief A method to check if the Shader compiled

	@param GLint - Pointing to the shader location
	@returns bool - Containing a true or false to if its compiled
	*/
	bool CheckShaderCompiled(GLint);
	/**
	@brief A method to initalise the shader
	@param std::string - Vertex Shader Path
	@param std::string - Fragment Shader Path
	@param GLuint& - GLuint reference to the ModelMatrix Location
	@param GLuint& - GLuint reference to the View Matrix Location
	@paran GLuint& - GLuint reference to the Project Matrix Location
	@param GLuint& - GLuint reference to the Program
	*/
	void initShader(std::string, std::string, GLuint&, GLuint&, GLuint&, GLuint&);
	/**
	@brief A method to read in a Shader File

	@param std::string - A string containing the path to the file
	@returns - std::string - A string containing the contents of the file.
	*/
	std::string ReadShaderFile(std::string);


private:


};

#endif