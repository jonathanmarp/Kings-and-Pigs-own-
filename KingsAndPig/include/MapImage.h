#ifndef MAP_IMAGE_H
#define MAP_IMAGE_H

// Include header <C++>
#include <string>
#include <vector>

// Include header <SDL2>
#include <SDL.h>

// Include header <3party>
#include <nlohmann/json.hpp>

/**
 * This struct for save data
 * Our texture
 */
struct MapImageStruct {
	// Texture
	SDL_Texture* data;

	// Tiles
	std::vector<std::vector<SDL_Rect>> tiles;
};

class MapImage {
private:
	// This variable for support converting
	SDL_Renderer* _render_;

	// This string will be target to path until file
	std::string pathToTexture;

	// This variable for saved data
	nlohmann::json _data_json_;

public:
	// This variable for save texture
	std::vector<MapImageStruct> textures;

public:
	// Constructor
	MapImage(SDL_Renderer* render, std::string path);

private:
	/**
	 * This function will call when intialize
	 * The constructor
	 */
	void Start();
};

#endif // MAP_IMAGE_H