#pragma once

#include "glm/glm.hpp"

class Mesh {
private:
	glm::vec3 rotation;
	glm::vec3 translation;
public:
	Mesh();
	~Mesh();

	glm::mat4 GetModelTransformMatrix();
};