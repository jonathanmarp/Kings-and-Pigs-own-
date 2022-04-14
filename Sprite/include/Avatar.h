#ifndef AVATAR_H
#define AVATAR_H

// Include header <SDL2>
#include <SDL.h>

// Include header <thirdpart>
#include <box2d/box2d.h>

// Include header <Kings and Pigs>
#include "MapImage.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "Core.h"

class Avatar {
private:
	// This variable used for core
	Core* core = nullptr;

	// This function used for texture
	MapImage* _mapImageTexture_ = nullptr;

	/**
	 * This variable used for know the
	 * position and size the door
	 */
	SDL_Rect rectDoor;

	/**
	 * This variable used for controller
	 * For sprite where it's need to go
	 */
	float speed = 20;
	float jumpForce = 100;
	int8_t direction = 1;

	/**
	 * This variable used for animation
	 */
	Animation* animation = nullptr;

	/**
	 * This variable used for physics
	 */
	Rigidbody* rigidbody = nullptr;
	int radius = 13;
public:
	// Constructor
	Avatar(Core* pCore, MapImage* mapImageTexture, b2World* world,
		int x, int y);
	
public:
	/**
	 * This function used for logic
	 * Animation or somehting else
	 */
	void Update();

	/**
	 * This function used to handle
	 * Event
	 */
	void Event();

	/**
	 * This function used for render
	 * Sprite
	 */
	void Render();
};

#endif // AVATAR_H