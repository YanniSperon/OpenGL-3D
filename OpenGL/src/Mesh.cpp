#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "primitives/ShapeGenerator.h"

Mesh::Mesh(type type, std::string dir, std::string name)
	: directory(directory), fileName(fileName), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), shape()
{
	if (type == type::triangle) {
		shape = ShapeGenerator::makeTriangle();
	}
	else if (type == type::cubeModel) {
		shape = ShapeGenerator::makeCube();
	}
	else if (type == type::blankModel) {
		shape = ShapeGenerator::loadShape(dir + name);
	}
	else if (type == type::texturedModel) {
		shape = ShapeGenerator::loadTexturedShape(dir, name);
	}
}

Mesh::~Mesh()
{

}

glm::mat4 Mesh::GetModelTransformMatrix()
{
	return (glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)));
}

void Mesh::rotate3f(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Mesh::rotatev(glm::vec3 rot) {
	rotation = rot;
}

void Mesh::translate3f(float x, float y, float z)
{
	translation.x = x;
	translation.y = y;
	translation.z = z;
}

void Mesh::translatev(glm::vec3 trans) {
	translation = trans;
}

ShapeData Mesh::GetShape()
{
	return shape;
}

void Mesh::SetShape(ShapeData newShape)
{
	shape = newShape;
}
