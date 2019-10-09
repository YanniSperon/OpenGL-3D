#pragma once
#include "Mesh.h"
#include "primitives/ShapeData.h"
#include "Shader.h"

class Object : public Mesh {
private:
	GLuint vertexBufferID;
	GLuint indexBufferID;
	GLuint texID;
	GLuint shaderID;
	GLsizei numIndices;
public:
	Object();
	Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, GLuint tex, GLuint shader);
	Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, GLuint tex, GLuint shader);
	~Object();

	void Draw();
	void Bind();
	void Unbind();
	unsigned int GetNumIndices();
	GLuint GetShaderID();
};