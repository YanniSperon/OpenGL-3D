#include "Camera.h"
#include "Config.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
	: hasControls(false), movementSpeed(0.1f), viewDirection(0.0f, 0.0f, -1.0f), upDirection(0.0f, 1.0f, 0.0f), cameraTranslation(0.0f, 0.0f, 0.0f), oldMouseX(0.0), oldMouseY(0.0), mouseSensitivity(0.0f)
{
	
}

Camera::Camera(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity)
	: hasControls(canControl), movementSpeed(movementSpeed), viewDirection(startingLookDirection), upDirection(startingUpDirection), 
	cameraTranslation(startingCameraTranslation), oldMouseX(0.0), oldMouseY(0.0), mouseSensitivity(mouseSensitivity)
{

}

Camera::~Camera()
{

}

void Camera::EnableMovementControls()
{
	hasControls = true;
}

void Camera::DisableMovementControls()
{
	hasControls = false;
}

glm::mat4 Camera::GetViewTransformMatrix()
{
	return glm::lookAt(cameraTranslation, cameraTranslation + viewDirection, upDirection);
}

void Camera::LookAt(double xpos, double ypos)
{
	if (hasControls) {
		glm::vec2 mouseDelta(xpos - oldMouseX, ypos - oldMouseY);

		// finds the vector perpendicular to both viewDirection and upDirection to find which axis to rotate  the camera around.
		glm::vec3 toRotateAround = glm::cross(viewDirection, upDirection);
		glm::vec3 vd;
		viewDirection = glm::mat3(
			glm::rotate(glm::mat4(1.0f), -mouseDelta.x * mouseSensitivity, upDirection) *
			glm::rotate(glm::mat4(1.0f), -mouseDelta.y * mouseSensitivity, toRotateAround)
		) * viewDirection;

		viewDirection = glm::mat3() * viewDirection;

		oldMouseX = xpos;
		oldMouseY = ypos;
	}
}

void Camera::MoveForward()
{
	if (hasControls) {
		cameraTranslation.x += movementSpeed * viewDirection.x;
		cameraTranslation.z += movementSpeed * viewDirection.z;
	}
}

void Camera::MoveBackward()
{
	if (hasControls) {
		cameraTranslation.x += -movementSpeed * viewDirection.x;
		cameraTranslation.z += -movementSpeed * viewDirection.z;
	}
}

void Camera::StrafeLeft()
{
	if (hasControls) {
		glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
		cameraTranslation.x += -movementSpeed * strafeDirection.x;
		cameraTranslation.z += -movementSpeed * strafeDirection.z;
	}
}

void Camera::StrafeRight()
{
	if (hasControls) {
		glm::vec3 strafeDirection = glm::cross(viewDirection, upDirection);
		cameraTranslation.x += movementSpeed * strafeDirection.x;
		cameraTranslation.z += movementSpeed * strafeDirection.z;
	}
}

void Camera::MoveUp()
{
	if (hasControls) {
		cameraTranslation += movementSpeed * upDirection;
	}
}

void Camera::MoveDown()
{
	if (hasControls) {
		cameraTranslation += -movementSpeed * upDirection;
	}
}

void Camera::ChangeMovementSpeed(float newSpeed)
{
	movementSpeed = newSpeed;
}

void Camera::BringWith(Mesh& obj)
{
	obj.TranslateVec3(cameraTranslation);
}

glm::vec3 Camera::GetTranslation()
{
	return cameraTranslation;
}
