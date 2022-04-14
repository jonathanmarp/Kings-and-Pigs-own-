#ifndef ANIMATION_H
#define ANIMATION_H

// Include header <SDL2>
#include <SDL.h>

// Include header <Important>
#include "MapImage.h"

class Animation {
private:
	// This function used for texture
	MapImage* _mapImageTexture_ = nullptr;

	// This variable for animation <Private>
	int indexAnimation = 0;
	int startTicks = 0;
	int animation_ = 0;

public:
	// This variable for animation <Public>
	int animation = 0;
	int delayAnimation = 100;
	int rowFrame = 0;
	bool repeat = true;

public:
	// Construction
	Animation(MapImage* mapImageTexture, bool pRepeat = true);

public:
	/**
	 * This function used for logic
	 */
	void Update();

	/**
	 * This function used for get
	 * Texture
	 */
	SDL_Texture* getTexture();

	/**
	 * This function used for get
	 * frame
	 */
	SDL_Rect* getFrame();
};

#endif // ANIMATION_H