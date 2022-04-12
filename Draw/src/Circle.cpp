// Include header <Self>
#include "../include/Circle.h"

/**
 * This function used to draw circle
 */
[[maybe_unused]] void Circle::Draw(SDL_Renderer* render, SDL_Color color, 
	int x_, int y_, int radius) {
    // Setup
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    // Set draw color
    SDL_SetRenderDrawColor(render,
        color.r, color.g, color.b, color.a);

    // Loop
    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(render, x_ + x, y_ - y);
        SDL_RenderDrawPoint(render, x_ + x, y_ + y);
        SDL_RenderDrawPoint(render, x_ - x, y_ - y);
        SDL_RenderDrawPoint(render, x_ - x, y_ + y);
        SDL_RenderDrawPoint(render, x_ + y, y_ - x);
        SDL_RenderDrawPoint(render, x_ + y, y_ + x);
        SDL_RenderDrawPoint(render, x_ - y, y_ - x);
        SDL_RenderDrawPoint(render, x_ - y, y_ + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}