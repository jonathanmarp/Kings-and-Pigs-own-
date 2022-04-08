#ifndef WORLD_H
#define WORLD_H

// Include header <C++>
#include <vector>

// Include header <SDL2>
#include <SDL.h>

// Include header <Important>
#include "MapImage.h"

// Include header <3party>
#include <nlohmann/json.hpp>

// Include header <Sprite>
#include "Door.h"

/**
 * Struct for sprite
 * Like image, and name of the images
 */
struct SpriteImages {
	std::string name = "";
	MapImage* mapImageSprite = nullptr;
};

class World {
private:
	// This variable for render
	SDL_Renderer* _render_ = nullptr;

	// This variable for json or data world
	nlohmann::json _data_world_ = nullptr;

	// This function used for texture
	MapImage* _mapImageTexture_ = nullptr;
	std::vector<SpriteImages> spriteTexture;

	// This function used to temp
	SDL_Rect destination = {};

	// This function used for sprite <Door>
	std::vector<Door*> doors;
public:
	// Constructor
	World(SDL_Renderer* render, nlohmann::json& data, 
		MapImage* mapImageTexture, nlohmann::json& dataSprite);

private:
	/**
	 * This function used for get data texture
	 */
	MapImage* GetTexture(std::string name);

public:
	/**
	 * This function used to logic
	 * or maybe something
	 */
	void Update();

	/**
	 * This function used to render the tiles
	 */
	void Render();
};

#endif // WORLD_H