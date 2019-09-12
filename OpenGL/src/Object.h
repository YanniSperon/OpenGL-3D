#pragma once
#include "Mesh.h"
#include "primitives/ShapeData.h"
#include "Shader.h"

class Object {
private:
	Mesh mesh;
	GLuint vertexArrayObjectID;
	GLuint vertexBufferID;
	GLuint indexBufferID;
	GLsizei numIndices;
	Shader shader;
public:
	Object();
	Object(type type, std::string dir, std::string name);
	~Object();

	void GLInit();
	void Rotate3f(float x, float y, float z);
	void RotateVec3(glm::vec3 rot);
	void Translate3f(float x, float y, float z);
	void TranslateVec3(glm::vec3 trans);
	void Draw();
	void Bind();
	void Unbind();
	/*void ChangeShape(ShapeData newShape);*/
	glm::mat4 GetModelTransformMatrix();
	void SetUniformMat4(const std::string& name, glm::mat4 mat);
};