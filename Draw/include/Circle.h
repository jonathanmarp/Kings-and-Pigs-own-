#ifndef CIRCLE_H
#define CIRCLE_H

// Include header <SDL2>
#include <SDL.h>

class Circle {
public:
	/**
	 * This function used to draw circle
	 */
	[[maybe_unused]] static void Draw(SDL_Renderer* render, SDL_Color color,
		int x_, int y_, int radius);
};

#endif // CIRCLE_H
