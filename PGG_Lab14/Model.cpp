#include "Model.h"

Model::Model()
{
	Program = 0;
	_textureLocation = _shaderModelMatLocation = _shaderViewMatLocation = _shaderProjMatLocation = 0;
}

void Model::draw(glm::mat4& VMatrix, glm::mat4& PMatrix)
{
	glUseProgram(Program);

	// Activate the VAO
	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
	_textureLocation = glGetUniformLocation(Program, "mytexture");
	glUniform1i(_textureLocation, 0);
	// Send matrices to the shader as uniforms
	glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(VMatrix));
	glUniformMatrix4fv(_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(PMatrix));


	glDrawArrays(GL_TRIANGLES, 0, numVerts);


	// Unbind VAO
	glBindVertexArray(0);
	glUseProgram(0);
}

void Model::loadTexture(std::string PATH)
{
	Texture = IMG_Load(PATH.c_str());
	if (Texture == NULL)
	{
		printf("%s\n", "Failed to Load Texture.");
	}
}

void Model::initVAO(std::string vPath, std::string fPath)
{
	numVerts = Mesh.Verts.size() / 3;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	int numtex = Mesh.texCoord.size() / 2;
	positionBuffer = 0;
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVerts * 3, &Mesh.Verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	normalBuffer = 0;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVerts * 3, &Mesh.Normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	textureCoord = 0;
	glGenBuffers(1, &textureCoord);
	glBindBuffer(GL_ARRAY_BUFFER, textureCoord);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float) * numtex * 2, &Mesh.texCoord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	

	shader.initShader(vPath, fPath, _shaderModelMatLocation, _shaderViewMatLocation, _shaderProjMatLocation, Program);

}

void Model::initTexture(std::string PATH)
{
	loadTexture(PATH);

	textureBuffer = 0;
	glGenTextures(1, &textureBuffer);
	//glGenBuffers(1, &textureBuffer);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		Texture->w,
		Texture->h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		Texture->pixels
		);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}
