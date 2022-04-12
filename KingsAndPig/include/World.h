#ifndef WORLD_H
#define WORLD_H

// Include header <C++>
#include <vector>

// Include header <SDL2>
#include <SDL.h>

// Include header <Important>
#include "MapImage.h"
#include "Core.h"

// Include header <3party>
#include <nlohmann/json.hpp>
#include <box2d/box2d.h>

// Include header <Sprite>
#include "Door.h"
#include "Avatar.h"

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
	// This variable for core
	Core* core = nullptr;

	// This variable for json or data world
	nlohmann::json _data_world_ = nullptr;

	// This function used for texture
	MapImage* _mapImageTexture_ = nullptr;
	std::vector<SpriteImages> spriteTexture;

	// This function used to temp
	SDL_Rect destination = {};

	// This function used for sprite <Door>
	std::vector<Door*> doors;

	// This function used for sprite <Door>
	std::vector<Avatar*> avatars;

	// This variable used for physics
	b2World* world;
	float timeStep = 1.0f / 20.0f;
	uint32_t velocityIterations = 6;
	uint32_t positionIterations = 2;
public:
	// Constructor
	World(Core* pCore, nlohmann::json& data,
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
	 * This function used to handle
	 * Event
	 */
	void Event();

	/**
	 * This function used to render the tiles
	 */
	void Render();
};

#endif // WORLD_H