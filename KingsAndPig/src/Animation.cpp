// Include header <Self>
#include "../include/Animation.h"

// Construction
Animation::Animation(MapImage* mapImageTexture, bool pRepeat)
	: _mapImageTexture_(mapImageTexture), repeat(pRepeat) {
	// Set tick
	this->startTicks = SDL_GetTicks();
}

/**
 * This function used for logic
 */
void Animation::Update() {
	// Animation
	// If animation bigger than delay
	if (SDL_GetTicks() - this->startTicks > this->delayAnimation) {
		// Update
		this->startTicks = SDL_GetTicks();

		// Increment
		this->indexAnimation += 1;
	}

	// Check if last frame
	if (this->indexAnimation >= 
		this->_mapImageTexture_->textures[animation].tiles[rowFrame].size()) {
		// If type is repeat
		if (this->repeat) {
			// Set into begin
			this->indexAnimation = 0;
		}

		// If type isn't repeat
		else {
			// Set into last
			this->indexAnimation = 
				this->_mapImageTexture_->textures[animation].tiles[rowFrame].size() - 1;
		}
	}
}

/**
 * This function used for get
 * Texture
 */
SDL_Texture* Animation::getTexture() {
	// return texture
	return this->_mapImageTexture_->textures[animation].data;
}

/**
 * This function used for get
 * frame
 */
SDL_Rect* Animation::getFrame() {
	// return frame
	return &this->_mapImageTexture_->textures[animation]
		.tiles[rowFrame][indexAnimation];
}