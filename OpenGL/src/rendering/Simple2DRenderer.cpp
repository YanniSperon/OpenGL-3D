#include "Simple2DRenderer.h"

int GetUniformLocation(const std::string& name, GLuint shaderID)
{
	int location = glGetUniformLocation(shaderID, name.c_str());
	if (location == -1)
		printf("Warning: uniform '%s' doesn't exist!", name.c_str());
	return location;
}

void UseProgram(GLuint program) {
	glUseProgram(program);
}

void SetUniformMat4f(const std::string& name, const glm::mat4& matrix, GLuint shaderID)
{
	glUniformMatrix4fv(GetUniformLocation(name, shaderID), 1, GL_FALSE, &matrix[0][0]);
}

void Simple2DRenderer::submit(Object* renderable, glm::vec3 camPos)
{
	glm::vec3 changeInValues = renderable->GetTranslation() - camPos;
	float distanceSquared = changeInValues.x * changeInValues.x + changeInValues.y * changeInValues.y;
	if (distanceSquared < 100.0f * 100.0f) {
		renderQueue.push_back(renderable);
	}
}

void Simple2DRenderer::submitForceRender(Object* renderable)
{
	renderQueue.push_back(renderable);
}

void Simple2DRenderer::flush(glm::mat4 view, glm::mat4 projection)
{
	glm::mat4 VP = projection * view;
	GLuint pastShader = 0;
	while (!renderQueue.empty())
	{
		Object* renderable = renderQueue.front();
		GLuint shaderID = renderable->GetShaderID();
		if (renderable->GetShaderID() != pastShader) {
			UseProgram(shaderID);
			SetUniformMat4f("VP", VP, shaderID);
			pastShader = shaderID;
		}
		SetUniformMat4f("M", renderable->GetModelTransformMatrix(), pastShader);
		renderable->Draw();
		renderQueue.pop_front();
	}
}
