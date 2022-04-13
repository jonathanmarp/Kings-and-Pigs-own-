// Include header <Self>
#include "../include/Avatar.h"

// Include header <C++>
#include <iostream>

// Include header <Draw>
#include "Circle.h"

// Constructor
Avatar::Avatar(Core* pCore, MapImage* mapImageTexture, b2World* world,
	int x, int y) : core(pCore), _mapImageTexture_(mapImageTexture) {
	// Intialize animation
	this->animation = new Animation(this->_mapImageTexture_);

	// Set position
	this->rectDoor.x = x;
	this->rectDoor.y = y;

	// Set size
	this->rectDoor.w = 78;
	this->rectDoor.h = 58;

	// Intialize rigidbody
	this->rigidbody = new Rigidbody();
	this->rigidbody->RigidBodyCircleInit(world,
		(float)this->rectDoor.x, (float)this->rectDoor.y,
		(float)this->rectDoor.w, (float)this->rectDoor.h,
		RigidBodyType::DYNAMIC, 20.0f);
}

/**
 * This function used to controll
 */
void Avatar::Event() {

}

/**
 * This function used for logic
 * Animation or somehting else
 */
void Avatar::Update() {
	// Update animation
	this->animation->Update();

	// Update position
	b2Vec2 position = this->rigidbody->body->GetPosition();
	this->rectDoor.x = (int)position.x;
	this->rectDoor.y = (int)position.y;
}

/**
 * This function used for render
 * Sprite
 */
void Avatar::Render() {
	// Render the sprite
	SDL_RenderCopy(this->core->GetRender(),
		this->animation->getTexture(),
		this->animation->getFrame(),
		&this->rectDoor);

	// Render circle
	Circle::Draw(this->core->GetRender(), { 0xff, 0xff, 0xff },
		this->rectDoor.x + (this->rectDoor.w / 2), this->rectDoor.y + (this->rectDoor.h / 2), 
		20);
}
