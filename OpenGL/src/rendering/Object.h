#pragma once
#include "Mesh.h"
#include "primitives/ShapeData.h"
#include "Shader.h"

class Object : public Mesh {
private:
	GLuint vertexBufferID;
	GLuint indexBufferID;
	GLuint texID;
	GLsizei numIndices;
	Shader shader;
public:
	Object();
	Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, GLuint tex);
	Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, GLuint tex);
	Object(glm::vec3 minCorner, glm::vec3 maxCorner, type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, GLuint tex, glm::vec4 topTexCoords, glm::vec4 bottomTexCoords, glm::vec4 leftTexCoords, glm::vec4 rightTexCoords, glm::vec4 frontTexCoords, glm::vec4 backTexCoords);
	~Object();

	void Draw(glm::mat4 view, glm::mat4 proj);
	void Bind();
	void Unbind();
	unsigned int GetNumIndices();
	///*void ChangeShape(ShapeData newShape);*/
	void SetUniformMat4(const std::string& name, glm::mat4 mat);
};