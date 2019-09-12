#pragma once

#include "glm/glm.hpp"
#include "primitives/ShapeData.h"
#include <string>

enum type
{
	triangle, cubeModel, blankModel, texturedModel
};

class Mesh {
private:
	std::string directory;
	std::string fileName;
	glm::vec3 rotation;
	glm::vec3 translation;
	ShapeData shape;
public:
	Mesh(type type, std::string dir, std::string name);
	~Mesh();

	glm::mat4 GetModelTransformMatrix();
	void rotate3f(float x, float y, float z);
	void rotatev(glm::vec3 rot);
	void translate3f(float x, float y, float z);
	void translatev(glm::vec3 trans);
	ShapeData GetShape();
	void SetShape(ShapeData newShape);
};