#include "ShapeGenerator.h"
#include "glm/glm.hpp"
#include "Vertex.h"
#include <fstream>
#include <string>
#include <vector>
#include <strstream>
#include <iostream>

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
		glm::vec3(+0.0f, +0.0f, +0.0f), // 0
		glm::vec3(+1.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(+1.0f, +0.0f, +0.0f), // 1
		glm::vec3(+0.0f, +1.0f, +0.0f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(+1.0f, +1.0f, +0.0f), // 2
		glm::vec3(+0.0f, +0.0f, +1.0f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(+0.0f, +1.0f, +0.0f), // 3
		glm::vec3(+1.0f, +1.0f, +1.0f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(+1.0f, +0.0f, +0.0f), // 4
		glm::vec3(+1.0f, +0.0f, +1.0f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(+1.0f, +0.0f, +1.0f), // 5
		glm::vec3(+0.0f, +0.5f, +0.2f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(+1.0f, +1.0f, +1.0f), // 6
		glm::vec3(+0.8f, +0.6f, +0.4f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(+1.0f, +1.0f, +0.0f), // 7
		glm::vec3(+0.3f, +1.0f, +0.5f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(+0.0f, +1.0f, +0.0f), // 8
		glm::vec3(+0.2f, +0.5f, +0.2f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(+1.0f, +1.0f, +0.0f), // 9
		glm::vec3(+0.9f, +0.3f, +0.7f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(+1.0f, +1.0f, +1.0f), // 10
		glm::vec3(+0.3f, +0.7f, +0.5f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(+0.0f, +1.0f, +1.0f), // 11
		glm::vec3(+0.5f, +0.7f, +0.5f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(+1.0f, +0.0f, +1.0f), // 12
		glm::vec3(+0.7f, +0.8f, +0.2f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(+0.0f, +0.0f, +1.0f), // 13
		glm::vec3(+0.5f, +0.7f, +0.3f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(+0.0f, +1.0f, +1.0f), // 14
		glm::vec3(+0.4f, +0.7f, +0.7f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(+1.0f, +1.0f, +1.0f), // 15
		glm::vec3(+0.2f, +0.5f, +1.0f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(+0.0f, +0.0f, +1.0f), // 16
		glm::vec3(+0.6f, +1.0f, +0.7f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(+0.0f, +0.0f, +0.0f), // 17
		glm::vec3(+0.6f, +0.4f, +0.8f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(+0.0f, +1.0f, +0.0f), // 18
		glm::vec3(+0.2f, +0.8f, +0.7f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(+0.0f, +1.0f, +1.0f), // 19
		glm::vec3(+0.2f, +0.7f, +1.0f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(+0.0f, +0.0f, +1.0f), // 20
		glm::vec3(+0.8f, +0.3f, +0.7f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(+1.0f, +0.0f, +1.0f), // 21
		glm::vec3(+0.8f, +0.9f, +0.5f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(+1.0f, +0.0f, +0.0f), // 22
		glm::vec3(+0.5f, +0.8f, +0.5f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(+0.0f, +0.0f, +0.0f), // 23
		glm::vec3(+0.9f, +1.0f, +0.2f), // color
		glm::vec2(+0.0f, +1.0f)         // texCoord
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2, // Front face
		0, 2, 3,

		4, 5, 6, // Right face
		4, 6, 7,

		8, 9, 10, // Top face
		8, 10, 11,

		12, 13, 14, // Back face
		12, 14, 15,

		16, 17, 18, // Left face
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
			positionsSize += 1;
		}

		if (line[0] == 'f')
		{
			unsigned int f[3];
			s >> junk >> f[0] >> f[1] >> f[2];
			indices.push_back(f[0] - 1);
			indices.push_back(f[1] - 1);
			indices.push_back(f[2] - 1);
			indicesSize += 3;
		}
	}

	ret.numVertices = positionsSize;
	ret.vertices = new Vertex[positionsSize];
	for (unsigned int i = 0; i < positionsSize; i++) {
		ret.vertices[i] = positions[i];
	}

	ret.numIndices = indicesSize;
	ret.indices = new GLuint[indicesSize];
	for (unsigned int k = 0; k < indicesSize; k++) {
		ret.indices[k] = indices[k];
	}

	return ret;
}

ShapeData ShapeGenerator::loadTexturedShape(std::string directory, std::string name)
{
	ShapeData ret;

	std::vector<Vertex> positions;
	std::vector<GLuint> indices;

	std::string fileName = directory + name;

	std::ifstream obj(fileName);

	unsigned int positionsSize = 0;
	unsigned int indicesSize = 0;

	if (!obj.is_open()) {
		return ret;
	}

	std::string mtlName;

	while (!obj.eof())
	{
		char line[128];
		obj.getline(line, 128);

		std::strstream s;
		s << line;

		std::string str(line);

		char junk;

		// Load materials from mtl file
		if (str.find("mtllib") != std::string::npos)
		{
			mtlName = str.substr(str.find("mtllib") + 7);
			std::cout << mtlName << std::endl;
			std::ifstream mtl(mtlName);

			std::string mtlFileName = directory + mtlName;

			bool fileLoadedProperly = true;

			if (!mtl.is_open()) {
				std::cout << "Error loading mtl file: \"" << mtlFileName << "\"\n";
				fileLoadedProperly = false;
			}
			while (!mtl.eof() && fileLoadedProperly)
			{
				char lineMTL[128];
				mtl.getline(lineMTL, 128);

				std::strstream sMTL;
				sMTL << lineMTL;

				std::string str(lineMTL);

				char junk;
				std::cout << "Loaded mtl file and grabbed line: " << lineMTL << "\n";
			}
		}
		// finished loading materials from mtl, now scan obj file for information referencing that file.
		//else if (str.find())
		else if (line[0] == 'v')
		{
			glm::vec3 v;
			s >> junk >> v.x >> v.y >> v.z;
			Vertex vert;
			vert.position = v;
			vert.color = glm::vec3(1.0f, 0.0f, 1.0f);
			positions.push_back(vert);
			positionsSize += 1;
		}
		else if (line[0] == 'f')
		{
			unsigned int f[3];
			s >> junk >> f[0] >> f[1] >> f[2];
			indices.push_back(f[0] - 1);
			indices.push_back(f[1] - 1);
			indices.push_back(f[2] - 1);
			indicesSize += 3;
		}
	}

	ret.numVertices = positionsSize;
	ret.vertices = new Vertex[positionsSize];
	for (unsigned int i = 0; i < positionsSize; i++) {
		ret.vertices[i] = positions[i];
	}

	ret.numIndices = indicesSize;
	ret.indices = new GLuint[indicesSize];
	for (unsigned int k = 0; k < indicesSize; k++) {
		ret.indices[k] = indices[k];
	}

	return ret;
}
