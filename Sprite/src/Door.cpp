// Include header <Self>
#include "../include/Door.h"

// Include header <C++>
#include <iostream>

// Constructor
Door::Door(SDL_Renderer* render, MapImage* mapImageTexture, 
	int x, int y) : _render_(render), _mapImageTexture_(mapImageTexture) {
	// Intialize animation
	this->animation = new Animation(this->_mapImageTexture_);

	// Set position
	this->rectDoor.x = std::move(x);
	this->rectDoor.y = std::move(y);

	// Set size
	this->rectDoor.w = 46;
	this->rectDoor.h = 56;
}

/**
 * This function used for logic
 * Animation or somehting else
 */
void Door::Update() {
	// Update animation
	this->animation->Update();
}

/**
 * This function used for render
 * Sprite
 */
void Door::Render() {
	// Render the sprite
	SDL_RenderCopy(this->_render_, 
		this->animation->getTexture(),
		this->animation->getFrame(),
		&this->rectDoor);
}