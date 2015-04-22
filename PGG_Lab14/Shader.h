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
	void initShader();
	std::string ReadShaderFile(std::string);
	GLuint& getProgram(){ return Program; };
	GLuint& getShaderMM(){ return ShaderMMLocation; };
	GLuint& getShaderVM(){ return ShaderPMLocation; };
	GLuint& getShaderPM(){ return ShaderVMLocation; };

private:
	GLuint Program;
	GLuint ShaderMMLocation, ShaderVMLocation, ShaderPMLocation;

};

#endif