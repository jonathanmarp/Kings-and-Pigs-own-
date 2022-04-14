// Include header <Self>
#include "../include/Rigidbody.h"

// Include header <C++>
#include <iostream>

/**
 * This function used for initialize ground
 */
[[maybe_unused]] void Rigidbody::RigidBodyGroundInit(b2World* world, float x, float y, 
	float w, float h) {
	// Setup body def
	this->bodyDef.type = b2_staticBody;
	this->bodyDef.position.Set(x, y);

	// Intialize body
	this->body = world->CreateBody(&this->bodyDef);

	// Setup shape
	b2PolygonShape shape;

	// Set size shape box
	shape.SetAsBox(w * (float)0.5, h * (float)0.5);

	// Create fixture on body
	this->body->CreateFixture(&shape, 0.0f);
}

/**
 * This function used for initialize
 */
[[maybe_unused]] void Rigidbody::RigidBodyCircleInit(b2World* world, float x, float y, 
	float w, float h, RigidBodyType type, float radius, float density, float friction,
	float resitution, float resitutionThreshold) {
	// Setup body def
	this->bodyDef.type = (b2BodyType)type;
	this->bodyDef.position.Set(x, y);

	// Intialize body
	this->body = world->CreateBody(&this->bodyDef);

	// Make shape
	b2CircleShape shape;

	// Set size shape circle
	shape.m_radius = radius;

	// Setup fixture
	this->fixtureDef.shape = &shape;

	this->fixtureDef.density = density;
	this->fixtureDef.friction = friction;
	this->fixtureDef.restitution = resitution;
	this->fixtureDef.restitutionThreshold = resitutionThreshold;

	// Create fixture on body
	this->body->CreateFixture(&this->fixtureDef);
}

/**
 * This function used for initialize
 * Box
 */
[[maybe_unused]] void Rigidbody::RigidBodyBoxInit(b2World* world, float x, float y, 
	float w, float h, RigidBodyType type, float radius,
	float density, float friction, float resitution, float resitutionThreshold) {
	// Setup body def
	this->bodyDef.type = (b2BodyType)type;
	this->bodyDef.position.Set(x, y);

	// Intialize body
	this->body = world->CreateBody(&this->bodyDef);

	// Make shape
	b2PolygonShape shape;

	// Set size shape circle
	shape.SetAsBox(w, h);

	// Setup fixture
	this->fixtureDef.shape = &shape;

	this->fixtureDef.density = density;
	this->fixtureDef.friction = friction;
	this->fixtureDef.restitution = resitution;
	this->fixtureDef.restitutionThreshold = resitutionThreshold;

	// Create fixture on body
	this->body->CreateFixture(&this->fixtureDef);
}