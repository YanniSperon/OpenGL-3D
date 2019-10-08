#include "ShapeGenerator.h"
#include "glm/glm.hpp"
#include "Vertex.h"
#include <fstream>
#include <string>
#include <vector>
#include <strstream>
#include <iostream>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a);

ShapeData ShapeGenerator::makeTriangle(glm::vec3& min, glm::vec3& max) {
	float minX = INFINITY;
	float minY = INFINITY;
	float minZ = INFINITY;

	float maxX = -INFINITY;
	float maxY = -INFINITY;
	float maxZ = -INFINITY;

	ShapeData ret;

	Vertex positions[] = {
		glm::vec3(-1.0f, -1.0f, +0.0f),     // 0
		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec2(+0.0f, +0.0f),

		glm::vec3(+1.0f, -1.0f, +0.0f),      // 1
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec2(+0.0f, +0.0f),

		glm::vec3(+0.0f, +1.0f, +0.0f),      // 2
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec2(+0.0f, +0.0f),
	};
	minX = -1.0f;
	minY = -1.0f;
	minZ = +0.0f;

	min = glm::vec3(minX, minY, minZ);
	max = glm::vec3(maxX, maxY, maxZ);

	maxX = +1.0f;
	maxY = +1.0f;
	maxZ = +0.0f;

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

ShapeData ShapeGenerator::makeCube(glm::vec3& min, glm::vec3& max)
{
	float minX = -INFINITY;
	float minY = -INFINITY;
	float minZ = -INFINITY;

	float maxX = -INFINITY;
	float maxY = -INFINITY;
	float maxZ = -INFINITY;
	
	ShapeData ret;

	Vertex positions[] = {
		glm::vec3(min.x, min.y, min.z), // 0
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(max.x, min.y, min.z), // 1
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(max.x, max.y, min.z), // 2
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(min.x, max.y, min.z), // 3
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(max.x, min.y, min.z), // 4
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(max.x, min.y, max.z), // 5
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(max.x, max.y, max.z), // 6
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(max.x, max.y, min.z), // 7
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(min.x, max.y, min.z), // 8
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(max.x, max.y, min.z), // 9
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(max.x, max.y, max.z), // 10
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(min.x, max.y, max.z), // 11
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(max.x, min.y, max.z), // 12
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(min.x, min.y, max.z), // 13
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(min.x, max.y, max.z), // 14
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(max.x, max.y, max.z), // 15
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(min.x, min.y, max.z), // 16
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(min.x, min.y, min.z), // 17
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(min.x, max.y, min.z), // 18
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(min.x, max.y, max.z), // 19
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord



		glm::vec3(min.x, min.y, max.z), // 20
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(max.x, min.y, max.z), // 21
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(max.x, min.y, min.z), // 22
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(min.x, min.y, min.z), // 23
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
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

ShapeData ShapeGenerator::loadShape(std::string fileName, glm::vec3& min, glm::vec3& max)
{
	float minX = INFINITY;
	float minY = INFINITY;
	float minZ = INFINITY;
	float maxX = -INFINITY;
	float maxY = -INFINITY;
	float maxZ = -INFINITY;
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
			if (vert.position.x < minX) {
				minX = vert.position.x;
			}
			else if (vert.position.x > maxX) {
				maxX = vert.position.x;
			}
			if (vert.position.y < minY) {
				minY = vert.position.y;
			}
			else if (vert.position.y > maxY) {
				maxY = vert.position.y;
			}
			if (vert.position.z < minZ) {
				minZ = vert.position.z;
			}
			else if (vert.position.z > maxZ) {
				maxZ = vert.position.z;
			}
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

ShapeData ShapeGenerator::loadTexturedShape(std::string directory, std::string name, glm::vec3& min, glm::vec3& max)
{
	float minX = INFINITY;
	float minY = INFINITY;
	float minZ = INFINITY;

	float maxX = -INFINITY;
	float maxY = -INFINITY;
	float maxZ = -INFINITY;

	ShapeData ret;

	std::vector<Vertex> positions;
	std::vector<GLuint> indices;
	std::vector<TexCoord> tempTex;

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
		char slash = '/';

		// Load materials from mtl file
		/*if (str.find("mtllib") != std::string::npos)
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
		}*/
		// finished loading materials from mtl, now scan obj file for information referencing that file.
		//else if (str.find())
		/*else*/ if (line[0] == 'v' && line[1] == ' ')
		{
			glm::vec3 v;
			s >> junk >> v.x >> v.y >> v.z;
			Vertex vert;
			vert.position = v;
			vert.color = glm::vec3(1.0f, 0.0f, 1.0f);
			if (vert.position.x < minX) {
				minX = vert.position.x;
			}
			else if (vert.position.x > maxX) {
				maxX = vert.position.x;
			}
			if (vert.position.y < minY) {
				minY = vert.position.y;
			}
			else if (vert.position.y > maxY) {
				maxY = vert.position.y;
			}
			if (vert.position.z < minZ) {
				minZ = vert.position.z;
			}
			else if (vert.position.z > maxZ) {
				maxZ = vert.position.z;
			}
			positions.push_back(vert);
			positionsSize += 1;
		}
		else if (line[0] == 'f' && line[1] == ' ')
		{
			unsigned int f[3];
			unsigned int uv[3];
			
			s >> junk >> f[0] >> slash >> uv[0] >>  f[1] >> slash >> uv[1] >> f[2] >> slash >> uv[2];
			indices.push_back(f[0] - 1);
			indices.push_back(f[1] - 1);
			indices.push_back(f[2] - 1);
			indicesSize += 3;
			positions[f[0] - 1].texCoord = glm::vec2(tempTex[uv[0] - 1].u, tempTex[uv[0] - 1].v);
			positions[f[1] - 1].texCoord = glm::vec2(tempTex[uv[1] - 1].u, tempTex[uv[1] - 1].v);
			positions[f[2] - 1].texCoord = glm::vec2(tempTex[uv[2] - 1].u, tempTex[uv[2] - 1].v);
		}
		else if (line[0] == 'v' && line[1] == 't') {
			float one;
			float two;
			std::string name;
			s >> name;
			s >> one;
			s >> two;
			TexCoord uv;
			uv.u = one;
			uv.v = two;
			tempTex.push_back(uv);
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

ShapeData ShapeGenerator::makeSkybox(glm::vec3& min, glm::vec3& max, glm::vec4 topTexCoords, glm::vec4 bottomTexCoords, glm::vec4 leftTexCoords, glm::vec4 rightTexCoords, glm::vec4 frontTexCoords, glm::vec4 backTexCoords)
{
	float minX = -INFINITY;
	float minY = -INFINITY;
	float minZ = -INFINITY;

	float maxX = -INFINITY;
	float maxY = -INFINITY;
	float maxZ = -INFINITY;

	ShapeData ret;

	Vertex positions[] = {
		// FRONT
		glm::vec3(min.x, min.y, min.z), // 0
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(frontTexCoords.x, frontTexCoords.y), // texCoord

		glm::vec3(max.x, min.y, min.z), // 1
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(frontTexCoords.z, frontTexCoords.y), // texCoord

		glm::vec3(max.x, max.y, min.z), // 2
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(frontTexCoords.z, frontTexCoords.w), // texCoord

		glm::vec3(min.x, max.y, min.z), // 3
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(frontTexCoords.x, frontTexCoords.w), // texCoord



		// RIGHT
		glm::vec3(max.x, min.y, min.z), // 4
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(rightTexCoords.x, rightTexCoords.y), // texCoord

		glm::vec3(max.x, min.y, max.z), // 5
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(rightTexCoords.z, rightTexCoords.y), // texCoord

		glm::vec3(max.x, max.y, max.z), // 6
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(rightTexCoords.z, rightTexCoords.w), // texCoord

		glm::vec3(max.x, max.y, min.z), // 7
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(rightTexCoords.x, rightTexCoords.w), // texCoord



		// TOP
		glm::vec3(min.x, max.y, min.z), // 8
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(topTexCoords.x, topTexCoords.y), // texCoord

		glm::vec3(max.x, max.y, min.z), // 9
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(topTexCoords.z, topTexCoords.y), // texCoord

		glm::vec3(max.x, max.y, max.z), // 10
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(topTexCoords.z, topTexCoords.w), // texCoord

		glm::vec3(min.x, max.y, max.z), // 11
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(topTexCoords.x, topTexCoords.w), // texCoord



		// BACK
		glm::vec3(max.x, min.y, max.z), // 12
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(backTexCoords.x, backTexCoords.y), // texCoord

		glm::vec3(min.x, min.y, max.z), // 13
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(backTexCoords.z, backTexCoords.y), // texCoord

		glm::vec3(min.x, max.y, max.z), // 14
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(backTexCoords.z, backTexCoords.w), // texCoord

		glm::vec3(max.x, max.y, max.z), // 15
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(backTexCoords.x, backTexCoords.w), // texCoord



		// LEFT
		glm::vec3(min.x, min.y, max.z), // 16
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(leftTexCoords.x, leftTexCoords.y), // texCoord

		glm::vec3(min.x, min.y, min.z), // 17
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(leftTexCoords.z, leftTexCoords.y), // texCoord

		glm::vec3(min.x, max.y, min.z), // 18
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(leftTexCoords.z, leftTexCoords.w), // texCoord

		glm::vec3(min.x, max.y, max.z), // 19
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(leftTexCoords.x, leftTexCoords.w), // texCoord



		// BOTTOM
		glm::vec3(min.x, min.y, max.z), // 20
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(bottomTexCoords.x, bottomTexCoords.y), // texCoord

		glm::vec3(max.x, min.y, max.z), // 21
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(bottomTexCoords.z, bottomTexCoords.y), // texCoord

		glm::vec3(max.x, min.y, min.z), // 22
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(bottomTexCoords.z, bottomTexCoords.w), // texCoord

		glm::vec3(min.x, min.y, min.z), // 23
		glm::vec3(+0.0f, +0.0f, +0.0f), // color
		glm::vec2(bottomTexCoords.x, bottomTexCoords.w), // texCoord
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
