#include "Shader.h"

Shader::Shader()
{
	Program = 0;
	ShaderMMLocation = ShaderPMLocation = ShaderVMLocation = 0;
	vShaderText = nullptr;
	fShaderText = nullptr;
}

Shader::~Shader()
{

}

bool Shader::CheckShaderCompiled(GLint shader)
{
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete[] log;

		return false;
	}
	return true;
}

void Shader::initShader()
{
	vshaderText = ReadShaderFile("vShader.txt");
	vShaderText = vshaderText.c_str();
	fshaderText = ReadShaderFile("fShader.txt");
	fShaderText = fshaderText.c_str();
	Program = glCreateProgram();
	// Create the vertex shader
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	// Give GL the source for it
	glShaderSource(vShader, 1, &vShaderText, NULL);
	// Compile the shader
	glCompileShader(vShader);
	// Check it compiled and give useful output if it didn't work!
	if (!CheckShaderCompiled(vShader))
	{
		return;
	}
	// This links the shader to the program
	glAttachShader(Program, vShader);

	// Same for the fragment shader
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	glCompileShader(fShader);
	if (!CheckShaderCompiled(fShader))
	{
		return;
	}
	glAttachShader(Program, fShader);

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram(Program);
	// Check this worked
	GLint linked;
	glGetProgramiv(Program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(Program, len, &len, log);
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete[] log;

		return;
	}

	// We need to get the location of the uniforms in the shaders
	// This is so that we can send the values to them from the application
	// We do this in the following way: 
	ShaderMMLocation = glGetUniformLocation(Program, "modelMat");
	ShaderVMLocation = glGetUniformLocation(Program, "viewMat");
	ShaderPMLocation = glGetUniformLocation(Program, "projMat");

}

std::string Shader::ReadShaderFile(std::string PATH)
{
	std::string content;
	std::ifstream fileStream(PATH, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << PATH << ". File does not exist." << std::endl;
		return NULL;
	}

	std::string line = "";

	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
//	const GLchar* shader = content.c_str();

	fileStream.close();
	return content;
}
