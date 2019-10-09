#include "Object.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image/stb_image.h"

Object::Object()
	: Mesh(), vertexBufferID(0), indexBufferID(0), numIndices(0), texID(0), shaderID(0)
{

}

Object::Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, GLuint tex, GLuint shader)
	: Mesh(minCorner, maxCorner, type, dir, name), shaderID(0), texID(0)
{
	texID = tex;

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Object::Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, GLuint tex, GLuint shader)
	: Mesh(minCorner, maxCorner, type, dir, name, rot, trans), shaderID(shader), texID(0)
{
	texID = tex;

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Object::Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, GLuint tex, GLuint shader, glm::vec4 topTexCoords, glm::vec4 bottomTexCoords, glm::vec4 leftTexCoords, glm::vec4 rightTexCoords, glm::vec4 frontTexCoords, glm::vec4 backTexCoords)
	: Mesh(minCorner, maxCorner, type, dir, name, rot, trans, topTexCoords, bottomTexCoords, leftTexCoords, rightTexCoords, frontTexCoords, backTexCoords), shaderID(shader), texID(0)
{
	texID = tex;

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Object::~Object()
{

}

void Object::Draw()
{
	Bind();
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}

void Object::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
}

void Object::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int Object::GetNumIndices()
{
	return numIndices;
}

GLuint Object::GetShaderID()
{
	return shaderID;
}
