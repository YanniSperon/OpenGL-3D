#pragma once
#include "Object.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "Shader.h"

class Renderer2D {
public:
	virtual void submit(Object* renderable, glm::vec3 camPos) = 0;
	virtual void submitForceRender(Object* renderable) = 0;
	virtual void flush(glm::mat4 view, glm::mat4 projection) = 0;
};