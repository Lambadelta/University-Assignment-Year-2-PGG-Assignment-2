#ifndef SHADER_H
#define SHADER_H
#include "glew.h"
#include <iostream>
#include <fstream>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();
	bool CheckShaderCompiled(GLint);
	void initShader(std::string, std::string, GLuint&, GLuint&, GLuint&, GLuint&);
	std::string ReadShaderFile(std::string);


private:


};

#endif