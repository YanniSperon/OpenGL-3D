#pragma once

#include "glm/glm.hpp"

class Camera {
private:
	bool hasControls;
	glm::vec3 viewDirection;
	glm::vec3 upDirection;
	double oldMouseX;
	double oldMouseY;
public:
	Camera();
	~Camera();
	glm::mat4 GetViewTransformMatrix();
	void LookAt(double xpos, double ypos);
};