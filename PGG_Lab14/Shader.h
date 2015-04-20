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
	GLchar* ReadShaderFile(std::string);
	GLuint& getProgram(){ return Program; };
	GLuint& getShaderMM(){ return ShaderMMLocation; };
	GLuint& getShaderVM(){ return ShaderPMLocation; };
	GLuint& getShaderPM(){ return ShaderVMLocation; };

private:
	const GLchar *vShaderText;
	const GLchar *fShaderText;
	GLuint Program;
	GLuint ShaderMMLocation, ShaderVMLocation, ShaderPMLocation;

};

#endif