#pragma once
#include "ShapeData.h"
#include <string>
class ShapeGenerator {
public:
	static ShapeData makeTriangle();
	static ShapeData makeCube();
	static ShapeData loadShape(std::string fileName);
	static ShapeData loadTexturedShape(std::string directory, std::string name);
};