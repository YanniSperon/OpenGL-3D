#include "Object.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

Object::Object()
	: mesh(type::triangle, "", ""), vertexArrayObjectID(0), vertexBufferID(0), indexBufferID(0), numIndices(0), shader()
{
	
}

Object::Object(type type, std::string dir, std::string name)
	: mesh(type, dir, name), vertexArrayObjectID(0), vertexBufferID(0), indexBufferID(0), numIndices(0), shader("res/shaders/Basic.shader")
{
	
}

Object::~Object()
{

}

void Object::GLInit()
{
	std::cout << "GLINIT\n";
	glGenVertexArrays(1, &vertexArrayObjectID);

	

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, mesh.GetShape().vertexBufferSize(), mesh.GetShape().vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.GetShape().indexBufferSize(), mesh.GetShape().indices, GL_STATIC_DRAW);
	GLsizei numIndices = (GLsizei)mesh.GetShape().numIndices;
	mesh.GetShape().cleanUp();


	glBindVertexArray(vertexArrayObjectID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	shader.Bind();
}

void Object::Rotate3f(float x, float y, float z)
{
	mesh.rotate3f(x, y, z);
}

void Object::RotateVec3(glm::vec3 rot)
{
	mesh.rotatev(rot);
}

void Object::Translate3f(float x, float y, float z)
{
	mesh.translate3f(x, y, z);
}

void Object::TranslateVec3(glm::vec3 trans)
{
	mesh.translatev(trans);
}

void Object::Draw()
{
	Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}

void Object::Bind()
{
	glBindVertexArray(vertexArrayObjectID);
}

void Object::Unbind()
{
	glBindVertexArray(0);
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

glm::mat4 Object::GetModelTransformMatrix()
{
	return mesh.GetModelTransformMatrix();
}

void Object::SetUniformMat4(const std::string& name, glm::mat4 mat)
{
	//std::cout << "set uniform\n";
	shader.Bind();
	shader.SetUniformMat4f(name, mat);
}
