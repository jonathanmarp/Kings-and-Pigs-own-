#ifndef LINE_H
#define LINE_H

// Include header <SDL2>
#include <SDL.h>

/**
 * This enum for type of draw
 * Line
 */
enum class LineType {
	ToLeft,
	ToRight,
	ToDown,
	ToUp
};

class Line {
public:
	/**
	 * This function used to draw line
	 * With width can be settings
	 */
	[[maybe_unused]] static void DrawLine(SDL_Renderer* render, uint8_t width, SDL_Color color,
		LineType type, int x1, int y1, int x2, int y2);
};

#endif // LINE_H