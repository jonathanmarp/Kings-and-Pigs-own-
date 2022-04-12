#ifndef RIGIDBODY_H
#define RIGIDBODY_H

// Include header <3party>
#include <box2d/box2d.h>

/**
 * This enum for type of physics
 */
enum class RigidBodyType {
	STATIC    = b2_staticBody,
	DYNAMIC   = b2_dynamicBody,
	KINEMATIC = b2_kinematicBody,
};

class Rigidbody {
private:
	/**
	 * This variable used for physics
	 * Settings
	 */
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;

public:
	// This variable for physics
	b2Body* body;

public:
	/**
	 * This function used for initialize ground
	 */
	void RigidBodyGroundInit(b2World* world, float x, float y, float w, float h);

	/**
	 * This function used for initialize
	 * Circle
	 */
	void RigidBodyCircleInit(b2World* world, float x, float y, float w, float h,
		RigidBodyType type, float radius,
		float density = 1.0f, float friction = 0.5f,
		float resitution = 0.0f, float resitutionThreshold = 0.5f);

	/**
	 * This function used for initialize
	 * Box
	 */
	void RigidBodyBoxInit(b2World* world, float x, float y, float w, float h,
		RigidBodyType type, float radius,
		float density = 1.0f, float friction = 0.5f,
		float resitution = 0.0f, float resitutionThreshold = 0.5f);
};

#endif // RIGIDBODY_H