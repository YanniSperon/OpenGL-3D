#pragma once
#include "ShapeData.h"
#include <string>
class ShapeGenerator {
public:
	static ShapeData makeTriangle(glm::vec3& min, glm::vec3& max);
	static ShapeData makeCube(glm::vec3& min, glm::vec3& max);
	static ShapeData loadShape(std::string fileName, glm::vec3& min, glm::vec3& max);
	static ShapeData loadTexturedShape(std::string directory, std::string name, glm::vec3& min, glm::vec3& max);
	static ShapeData makeSkybox(glm::vec3& min, glm::vec3& max, glm::vec4 topTexCoords, glm::vec4 bottomTexCoords, glm::vec4 leftTexCoords, glm::vec4 rightTexCoords, glm::vec4 frontTexCoords, glm::vec4 backTexCoords);
};