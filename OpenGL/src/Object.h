#pragma once
#include "Mesh.h"
#include "primitives/ShapeData.h"
#include "Shader.h"

class Object : public Mesh {
private:
	GLuint vertexBufferID;
	GLuint indexBufferID;
	GLsizei numIndices;
	Shader shader;
public:
	Object();
	Object(type type, std::string dir, std::string name);
	~Object();

	void Bind();
	void Unbind();
	unsigned int GetNumIndices();
	///*void ChangeShape(ShapeData newShape);*/
	void SetUniformMat4(const std::string& name, glm::mat4 mat);
};