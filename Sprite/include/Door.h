#ifndef DOOR_H
#define DOOR_H

// Include header <SDL2>
#include <SDL.h>

// Include header <Kings and Pigs>
#include "MapImage.h"
#include "Animation.h"

class Door {
private:
	// This variable used for render
	SDL_Renderer* _render_;

	// This function used for texture
	MapImage* _mapImageTexture_ = nullptr;

	/**
	 * This variable used for know the 
	 * position and size the door
	 */
	SDL_Rect rectDoor;
	
	/**
	 * This variable used for animation
	 */
	Animation* animation = nullptr;
public:
	// Constructor
	Door(SDL_Renderer* render, MapImage* mapImageTexture, 
		int x, int y);

public:
	/**
	 * This function used for logic
	 * Animation or somehting else
	 */
	void Update();

	/**
	 * This function used for render
	 * Sprite
	 */
	void Render();
};

#endif // DOOR_H