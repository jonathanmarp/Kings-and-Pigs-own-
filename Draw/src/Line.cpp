// Include header <Self>
#include "../include/Line.h"

/**
 * This function used to draw line
 * With width can be settings
 */
[[maybe_unused]] void Line::Draw(SDL_Renderer* render, uint8_t width, SDL_Color color, LineType type,
	int x1, int y1, int x2, int y2) {
	// Set draw color
	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);

	// Loop for width
	for (uint8_t i = 0; i < width; i++) {
		// Render line
		SDL_RenderDrawLine(render, x1, y1, x2, y2);

		// Logical
		switch (type) {
			using enum LineType;

			// <Down>
			[[likely]] case LineType::ToDown: {
				y1 += 1;
				y2 += 1;
			} break;

			// <Up>
			[[unlikely]] case LineType::ToUp: {
				y1 -= 1;
				y2 -= 1;
			} break;

			// <Left>
			[[unlikely]] case LineType::ToLeft: {
				x1 -= 1;
				x2 -= 1;
			} break;

			// <Right>
			[[likely]] case LineType::ToRight: {
				x1 += 1;
				x2 += 1;
			} break;
		}
	}
}