#include "Object.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

Object::Object()
	: Mesh(), indexBufferID(0), numIndices(0), vertexBufferID(0)
	//: mesh(type::triangle, "", ""), vertexArrayObjectID(0), vertexBufferID(0), indexBufferID(0), numIndices(0), shader()
{
}

Object::Object(type type, std::string dir, std::string name)
	: Mesh(type, dir, name), shader("res/shaders/Basic.shader")
	//: mesh(type, dir, name), vertexArrayObjectID(0), vertexBufferID(0), indexBufferID(0), numIndices(0), shader("res/shaders/Basic.shader")
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

//void Object::GLInit()
//{
//	
//}
//
//void Object::Rotate3f(float x, float y, float z)
//{
//	mesh.rotate3f(x, y, z);
//}
//
//void Object::RotateVec3(glm::vec3 rot)
//{
//	mesh.rotatev(rot);
//}
//
//void Object::Translate3f(float x, float y, float z)
//{
//	mesh.translate3f(x, y, z);
//}
//
//void Object::TranslateVec3(glm::vec3 trans)
//{
//	mesh.translatev(trans);
//}
//
//void Object::Draw()
//{
//	
//}
//
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

//glm::mat4 Object::GetModelTransformMatrix()
//{
//	glm::mat4 modelTransformMatrix = mesh.GetModelTransformMatrix();
//	for (unsigned int i = 0; i < 4; i++) {
//		for (unsigned int j = 0; j < 4; j++) {
//			std::cout << modelTransformMatrix[i][j];
//		}
//		std::cout << std::endl;
//	}
//	return modelTransformMatrix;
//}

void Object::SetUniformMat4(const std::string& name, glm::mat4 mat)
{
	shader.SetUniformMat4f(name, mat);
}
