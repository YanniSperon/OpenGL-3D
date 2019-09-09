#include "ShapeGenerator.h"
#include "glm/glm.hpp"
#include "Vertex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <strstream>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a);

ShapeData ShapeGenerator::makeTriangle() {
	ShapeData ret;

	Vertex positions[] = {
		glm::vec3(-1.0f, -1.0f, +0.0f),     // 0
		glm::vec3(+0.0f, +1.0f, +0.0f),

		glm::vec3(+1.0f, -1.0f, +0.0f),      // 1
		glm::vec3(+0.0f, +0.0f, +1.0f),

		glm::vec3(+0.0f, +1.0f, +0.0f),      // 2
		glm::vec3(+1.0f, +0.0f, +0.0f),
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLuint[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

ShapeData ShapeGenerator::makeCube()
{
	ShapeData ret;

	Vertex positions[] = {
		glm::vec3(-1.0f, +1.0f, +1.0f), // 0
		glm::vec3(+1.0f, +0.0f, +0.0f), // color

		glm::vec3(+1.0f, +1.0f, +1.0f), // 1
		glm::vec3(+0.0f, +1.0f, +0.0f), // color

		glm::vec3(+1.0f, +1.0f, -1.0f), // 2
		glm::vec3(+0.0f, +0.0f, +1.0f), // color

		glm::vec3(-1.0f, +1.0f, -1.0f), // 3
		glm::vec3(+1.0f, +1.0f, +1.0f), // color



		glm::vec3(-1.0f, +1.0f, -1.0f), // 4
		glm::vec3(+1.0f, +0.0f, +1.0f), // color

		glm::vec3(+1.0f, +1.0f, -1.0f), // 5
		glm::vec3(+0.0f, +0.5f, +0.2f), // color

		glm::vec3(+1.0f, -1.0f, -1.0f), // 6
		glm::vec3(+0.8f, +0.6f, +0.4f), // color

		glm::vec3(-1.0f, -1.0f, -1.0f), // 7
		glm::vec3(+0.3f, +1.0f, +0.5f), // color



		glm::vec3(+1.0f, +1.0f, -1.0f), // 8
		glm::vec3(+0.2f, +0.5f, +0.2f), // color

		glm::vec3(+1.0f, +1.0f, +1.0f), // 9
		glm::vec3(+0.9f, +0.3f, +0.7f), // color

		glm::vec3(+1.0f, -1.0f, +1.0f), // 10
		glm::vec3(+0.3f, +0.7f, +0.5f), // color

		glm::vec3(+1.0f, -1.0f, -1.0f), // 11
		glm::vec3(+0.5f, +0.7f, +0.5f), // color



		glm::vec3(-1.0f, +1.0f, +1.0f), // 12
		glm::vec3(+0.7f, +0.8f, +0.2f), // color

		glm::vec3(-1.0f, +1.0f, -1.0f), // 13
		glm::vec3(+0.5f, +0.7f, +0.3f), // color

		glm::vec3(-1.0f, -1.0f, -1.0f), // 14
		glm::vec3(+0.4f, +0.7f, +0.7f), // color

		glm::vec3(-1.0f, -1.0f, +1.0f), // 15
		glm::vec3(+0.2f, +0.5f, +1.0f), // color



		glm::vec3(+1.0f, +1.0f, +1.0f), // 16
		glm::vec3(+0.6f, +1.0f, +0.7f), // color

		glm::vec3(-1.0f, +1.0f, +1.0f), // 17
		glm::vec3(+0.6f, +0.4f, +0.8f), // color

		glm::vec3(-1.0f, -1.0f, +1.0f), // 18
		glm::vec3(+0.2f, +0.8f, +0.7f), // color

		glm::vec3(+1.0f, -1.0f, +1.0f), // 19
		glm::vec3(+0.2f, +0.7f, +1.0f), // color



		glm::vec3(+1.0f, -1.0f, -1.0f), // 20
		glm::vec3(+0.8f, +0.3f, +0.7f), // color

		glm::vec3(-1.0f, -1.0f, -1.0f), // 21
		glm::vec3(+0.8f, +0.9f, +0.5f), // color

		glm::vec3(-1.0f, -1.0f, +1.0f), // 22
		glm::vec3(+0.5f, +0.8f, +0.5f), // color

		glm::vec3(+1.0f, -1.0f, +1.0f), // 23
		glm::vec3(+0.9f, +1.0f, +0.2f), // color
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2, // Top face
		0, 2, 3,
		
		4, 5, 6, // Front face
		4, 6, 7,

		8, 9, 10, // Right face
		8, 10, 11,

		12, 13, 14, // Left face
		12, 14, 15,

		16, 17, 18, // Back face
		16, 18, 19,

		20, 22, 21, // Bottom face
		20, 23, 22
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLuint[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

ShapeData ShapeGenerator::loadShape(std::string fileName)
{
	ShapeData ret;

	std::vector<Vertex> positions;
	std::vector<GLuint> indices;

	std::ifstream f(fileName);

	unsigned int positionsSize = 0;
	unsigned int indicesSize = 0;

	if (!f.is_open()) {
		return ret;
	}

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v')
		{
			glm::vec3 v;
			s >> junk >> v.x >> v.y >> v.z;
			Vertex vert;
			vert.position = v;
			vert.color = glm::vec3(1.0f, 1.0f, 1.0f);
			positions.push_back(vert);
			std::cout << "Vertex: " << v.x << ", " << v.y << ", " << v.z << std::endl;
			std::cout << "Color: " << vert.color.r << ", " << vert.color.g << ", " << vert.color.b << std::endl;
			positionsSize += 1;
		}

		if (line[0] == 'f')
		{
			int f[3];
			s >> junk >> f[0] >> f[1] >> f[2];
			indices.push_back(f[0] - 1);
			indices.push_back(f[1] - 1);
			indices.push_back(f[2] - 1);
			std::cout << "Index: " << f[0]-1 << ", " << f[1] - 1 << ", " << f[2] - 1 << std::endl;
			indicesSize += 1;
		}
	}

	std::cout << positionsSize << std::endl;
	std::cout << indicesSize << std::endl;

	ret.numVertices = positionsSize;
	ret.vertices = new Vertex[positionsSize];
	for (unsigned int i = 0; i < positionsSize; i++) {
		ret.vertices[i] = positions[i];
	}

	ret.numIndices = indicesSize;
	ret.indices = new GLuint[indicesSize];
	for (unsigned int i = 0; i < indicesSize; i++) {
		ret.indices[i] = indices[i];
	}

	return ret;
}
