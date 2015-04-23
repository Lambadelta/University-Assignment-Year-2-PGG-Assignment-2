#include "Model.h"

Model::Model()
{
	Program = 0;
	_shaderModelMatLocation = _shaderViewMatLocation = _shaderProjMatLocation = 0;
}

void Model::draw(glm::mat4& VMatrix, glm::mat4& PMatrix)
{
	glUseProgram(Program);

	// Activate the VAO
	glBindVertexArray(VAO);
	// Send matrices to the shader as uniforms
	glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(VMatrix));
	glUniformMatrix4fv(_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(PMatrix));

	glDrawArrays(GL_TRIANGLES, 0, numVerts);

	// Unbind VAO
	glBindVertexArray(0);

	glUseProgram(0);
}

void Model::initVAO(std::string vPath, std::string fPath)
{
	numVerts = Mesh.Verts.size() / 3;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint positionBuffer = 0;
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVerts * 3, &Mesh.Verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	GLuint normalBuffer = 0;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVerts * 3, &Mesh.Normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	shader.initShader(vPath, fPath, _shaderModelMatLocation, _shaderViewMatLocation, _shaderProjMatLocation, Program);

}
