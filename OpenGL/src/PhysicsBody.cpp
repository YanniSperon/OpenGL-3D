#include "PhysicsBody.h"

PhysicsBody::PhysicsBody()
	: Object(), mass(1), vX(0), vY(0), vZ(0), fX(0), fY(0), fZ(0), momentOfInertia(1), wX(0), wY(0), wZ(0), tX(0), tY(0), tZ(0), centerOfGravity(0.0f, 0.0f, 0.0f)
{

}

PhysicsBody::PhysicsBody(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName)
	: Object(type, dir, name, rot, trans, texDir, texName), mass(1), vX(0), vY(0), vZ(0), fX(0), fY(0), fZ(0), momentOfInertia(1), wX(0), wY(0), wZ(0), tX(0), tY(0), tZ(0), centerOfGravity(0.0f, 0.0f, 0.0f)
{

}

PhysicsBody::PhysicsBody(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName, float m, float velX, float velY, float velZ, float forceX, float forceY, float forceZ, float MOI, float angVelX, float angVelY, float angVelZ, float torqueX, float torqueY, float torqueZ, glm::vec3 COG)
	: Object(type, dir, name, rot, trans, texDir, texName), mass(m), vX(velX), vY(velY), vZ(velZ), fX(forceX), fY(forceY), fZ(forceZ), momentOfInertia(MOI), wX(angVelX), wY(angVelY), wZ(angVelZ), tX(torqueX), tY(torqueY), tZ(torqueZ), centerOfGravity(COG)
{

}

PhysicsBody::~PhysicsBody()
{

}

float PhysicsBody::GetDistance(glm::vec3 pos1, glm::vec3 pos2)
{
	return sqrtf(((pos2.x - pos1.x) * (pos2.x - pos1.x)) + ((pos2.y - pos1.y) * (pos2.y - pos1.y)) + ((pos2.z - pos1.z) * (pos2.z - pos1.z)));
}

glm::vec3 PhysicsBody::GetAngularAcceleration()
{
	return glm::vec3();
}

glm::vec3 PhysicsBody::GetLinearAcceleration()
{
	return glm::vec3();
}

void PhysicsBody::Update(float time)
{
	if (GetTranslation().y <= -3.0f) {
		Stop();
	}
	float oneOverMass = 1 / mass;
	float deltaLinTemp = 0.5 * (oneOverMass)* time * time;
	float deltaX = vX * time + fX * deltaLinTemp;
	float deltaY = vY * time + fY * deltaLinTemp;
	float deltaZ = vZ * time + fZ * deltaLinTemp;
	TranslateAdd3f(deltaX, deltaY, deltaZ);
	float linTemp = (oneOverMass) * time;
	vX += fX * linTemp;
	vY += fY * linTemp;
	vZ += fZ * linTemp;

	float oneOverMOI = 1 / momentOfInertia;
	float deltaAngTemp = 0.5 * (oneOverMOI)* time * time;
	float deltaOmegaX = wX * time + tX * deltaAngTemp;
	float deltaOmegaY = wY * time + tY * deltaAngTemp;
	float deltaOmegaZ = wZ * time + tZ * deltaAngTemp;
	RotateAdd3f(deltaOmegaX, deltaOmegaY, deltaOmegaZ);
	float angTemp = (oneOverMOI) * time;
	wX += tX * angTemp;
	wY += tY * angTemp;
	wZ += tZ * angTemp;
}

void PhysicsBody::ApplyForce(glm::vec3 force)
{
	fX += force.x;
	fY += force.y;
	fZ += force.z;
}

void PhysicsBody::ApplyTorque(glm::vec3 force, glm::vec3 at)
{
	float distX = at.x - centerOfGravity.x;
	float distY = at.y - centerOfGravity.y;
	float distZ = at.z - centerOfGravity.z;

	tX += distX * force.x;
	tY += distY * force.y;
	tZ += distZ * force.z;
}

void PhysicsBody::ApplyForce(glm::vec3 force, glm::vec3 at)
{
	fX += force.x;
	fY += force.y;
	fZ += force.z;

	float distX = at.x - centerOfGravity.x;
	float distY = at.y - centerOfGravity.y;
	float distZ = at.z - centerOfGravity.z;

	tX += distX * force.x;
	tY += distY * force.y;
	tZ += distZ * force.z;
}

void PhysicsBody::ApplyImpulse(glm::vec3 force, float deltaT)
{

}

void PhysicsBody::ApplyAngularImpulse()
{

}

void PhysicsBody::ApplyImpulse(glm::vec3 force, glm::vec3 at, float deltaT)
{

}

void PhysicsBody::ApplyVelocity(glm::vec3 velocity)
{
	vX += velocity.x;
	vY += velocity.y;
	vZ += velocity.z;
}

void PhysicsBody::ApplyAngularVelocity(glm::vec3 velocity)
{
	wX += velocity.x;
	wY += velocity.y;
	wZ += velocity.z;
}

void PhysicsBody::Stop()
{
	vX = vY = vZ = fX = fY = fZ = wX = wY = wZ = tX = tY = tZ = 0;
}
