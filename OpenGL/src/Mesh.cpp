#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

Mesh::Mesh()
	: rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f)
{
	
}

Mesh::~Mesh()
{

}

glm::mat4 Mesh::GetModelTransformMatrix()
{
	return (glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)));
}
