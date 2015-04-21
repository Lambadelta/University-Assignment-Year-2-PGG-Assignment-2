#include "PlayerEntity.h"

PlayerEntity::PlayerEntity() : Model()
{
	VAO = 0;
	numVerts = 0;

	//initVAO();
}

PlayerEntity::~PlayerEntity()
{

}

void PlayerEntity::draw(glm::mat4& VMatrix, glm::mat4& PMatrix)
{
	glUseProgram(shader.getProgram());

	// Activate the VAO
	glBindVertexArray(VAO);
		// Send matrices to the shader as uniforms
		glUniformMatrix4fv(shader.getShaderMM(), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		glUniformMatrix4fv(shader.getShaderVM(), 1, GL_FALSE, glm::value_ptr(VMatrix));
		glUniformMatrix4fv(shader.getShaderPM(), 1, GL_FALSE, glm::value_ptr(PMatrix));

	glDrawArrays(GL_TRIANGLES, 0, numVerts);

	// Unbind VAO
	glBindVertexArray(0);

	glUseProgram(0);
}

void PlayerEntity::update(float dt)
{
	ModelMatrix = glm::translate(glm::mat4(1.0F), Position);
	ModelMatrix = glm::rotate(ModelMatrix, Rotation.y, glm::vec3(0, 1, 0));
}

void PlayerEntity::initVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		GLuint positionBuffer = 0;
		glGenBuffers(1, &positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Mesh.Verts) * 3, &Mesh.Verts[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		GLuint normalBuffer = 0;
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Mesh.Normals) * 3, &Mesh.Normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	numVerts = Mesh.Verts.size();
	shader.initShader();

}