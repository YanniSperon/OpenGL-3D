#include "Camera.h"

Camera::Camera()
	: hasControls(false), viewDirection(0.0f, 0.0f, -1.0f), upDirection(0.0f, 1.0f, 0.0f)
{
	
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewTransformMatrix()
{
	
}

void Camera::LookAt(double xpos, double ypos)
{
	glm::vec2 mouseDelta(xpos - oldMouseX, ypos - oldMouseY);

	glm::vec3 toRotateAround = glm::cross(viewDirection, upDirection);

	viewDirection = glm::mat3(
		glm::rotate(glm::mat4(1.0f), -mouseDelta.x * mouseSensitivity, upDirection) *
		glm::rotate(glm::mat4(1.0f), -mouseDelta.y * mouseSensitivity, toRotateAround)
	) * viewDirection;

	viewDirection = glm::mat3() * viewDirection;

	oldMouseX = xpos;
	oldMouseY = ypos;
}
