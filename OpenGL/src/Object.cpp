#include "Object.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

Object::Object()
	: Mesh(), vertexArrayObjectID(0), vertexBufferID(0), indexBufferID(0), numIndices(0)
{
}

Object::Object(type type, std::string dir, std::string name)
	: Mesh(type, dir, name), shader("res/shaders/Basic.shader")
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();

	shader.Bind();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader.Unbind();
}

Object::Object(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans)
	: Mesh(type, dir, name, rot, trans), shader("res/shaders/Basic.shader")
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();

	shader.Bind();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader.Unbind();
}

Object::~Object()
{

}

void Object::Draw(glm::mat4 view, glm::mat4 proj)
{
	Bind();
	glm::mat4 MVP = proj * view * GetModelTransformMatrix();
	shader.SetUniformMat4f("MVP", MVP);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}

void Object::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	shader.Bind();
}

void Object::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader.Unbind();
}

unsigned int Object::GetNumIndices()
{
	return numIndices;
}

//void Object::ChangeShape(ShapeData newShape)
//{
//	mesh.SetShape(newShape);
//	Bind();
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
//	glBufferData(GL_ARRAY_BUFFER, mesh.GetShape().vertexBufferSize(), mesh.GetShape().vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.GetShape().indexBufferSize(), mesh.GetShape().indices, GL_STATIC_DRAW);
//	numIndices = (GLsizei)mesh.GetShape().numIndices;
//}

void Object::SetUniformMat4(const std::string& name, glm::mat4 mat)
{
	shader.SetUniformMat4f(name, mat);
}
