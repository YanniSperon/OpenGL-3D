#pragma once
#include "Object.h"
#include "glm/glm.hpp"

class PhysicsBody : public Object {
private:
	float mass;
	float vX;
	float vY;
	float vZ;
	float fX;
	float fY;
	float fZ;
	float momentOfInertia;
	float wX;
	float wY;
	float wZ;
	float tX;
	float tY;
	float tZ;
	glm::vec3 centerOfGravity;
public:
	PhysicsBody();
	PhysicsBody(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName);
	PhysicsBody(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName,
		float m, float velX, float velY, float velZ, float forceX, float forceY, float forceZ, float MOI, float angVelX, float angVelY, float angVelZ, 
		float torqueX, float torqueY, float torqueZ, glm::vec3 COG);
	~PhysicsBody();

	float GetDistance(glm::vec3 pos1, glm::vec3 pos2);

	glm::vec3 GetAngularAcceleration();
	glm::vec3 GetLinearAcceleration();

	void Update(float time);

	void ApplyForce(glm::vec3 force);
	void ApplyTorque(glm::vec3 force, glm::vec3 at);
	void ApplyForce(glm::vec3 force, glm::vec3 at);
	void ApplyImpulse(glm::vec3 force, float deltaT);
	void ApplyAngularImpulse();
	void ApplyImpulse(glm::vec3 force, glm::vec3 at, float deltaT);
	void ApplyVelocity(glm::vec3 velocity);
	void ApplyAngularVelocity(glm::vec3 velocity);
	void Stop();
};