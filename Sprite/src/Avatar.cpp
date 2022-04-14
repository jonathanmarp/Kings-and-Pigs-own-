// Include header <Self>
#include "../include/Avatar.h"

// Include header <C++>
#include <iostream>
#include <future>

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
		(float)this->rectDoor.x + ((float)this->rectDoor.w / 2), 
		(float)this->rectDoor.y + ((float)this->rectDoor.h / 2),
		(float)this->rectDoor.w, (float)this->rectDoor.h,
		RigidBodyType::DYNAMIC, (float)this->radius);
	this->rigidbody->body->SetFixedRotation(true);
}

/**
 * This function used to controll
 */
void Avatar::Event() {
	// Switch
	switch (this->core->GetEvent()->type) {
		using enum SDL_EventType;

		// When key pressed
		[[likely]] case SDL_KEYDOWN: {
			// If <Condition [Keyboard]>
			const SDL_Keycode& key = this->core->GetEvent()->key.keysym.sym;
			
			// Setup for velocity
			b2Vec2 velocity = { 0, 0 };

			// If left
			if (key == SDLK_LEFT) {
				// Set direction
				this->direction = -1;

				// Sum into velocity x
				velocity.x += this->speed * this->direction;
			}

			// If left
			if (key == SDLK_RIGHT) {
				// Set direction
				this->direction = 1;

				// Sum into velocity x
				velocity.x += this->speed * this->direction;
			}

			// If left
			if (key == SDLK_SPACE) {
				// Set velocity y
				velocity.y += -(this->rigidbody->body->GetMass() * this->jumpForce);
			}

			// Set velocity
			// If run
			if (velocity.x != 0) {
				// Set animation into run
				this->animation->animation = 1;
			}

			// Set velocity
			this->rigidbody->body->SetLinearVelocity(
				b2Vec2(velocity.x, velocity.y));
		} break;

		[[likely]] case SDL_KEYUP: {
			// Set animation into idle
			this->animation->animation = 0;

			this->rigidbody->body->SetLinearVelocity(b2Vec2(0, 0));
		} break;
	}
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
	this->rectDoor.x = (int)position.x - (this->rectDoor.w / 2);
	this->rectDoor.y = (int)position.y - (this->rectDoor.h / 2);
}

/**
 * This function used for render
 * Sprite
 */
void Avatar::Render() {
	// Render the sprite
	std::async(std::launch::async,
		SDL_RenderCopyEx, 
		this->core->GetRender(),
		this->animation->getTexture(),
		this->animation->getFrame(),
		&this->rectDoor, 0, (SDL_Point*)NULL,
		SDL_RendererFlip(((this->direction == -1) ? 
			SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE)));

	// Render circle
	std::async(std::launch::async, Circle::Draw, 
		this->core->GetRender(), SDL_Color({ 0xff, 0xff, 0xff }),
		this->rectDoor.x + (this->rectDoor.w / 2),
		this->rectDoor.y + (this->rectDoor.h / 2),
		this->radius + 2);
}
