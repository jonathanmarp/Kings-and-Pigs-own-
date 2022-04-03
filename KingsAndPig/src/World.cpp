// Include header <Self>
#include "../include/World.h"

// Include header <C++>
#include <iostream>

// Constructor
World::World(SDL_Renderer* render, nlohmann::json data, 
	MapImage* mapImageTexture, MapImage* mapImageSprite)
	: _render_(render), _data_world_(data), 
	  _mapImageTexture_(mapImageTexture), _mapImageSprite_(mapImageSprite) {
	// Map <Array>
	for (auto item : this->_data_world_.items()) {
		// Setup variable for checking types
		std::string types = item.value()["type"].get<std::string>();

		// Check if the tile
		if (types == "door") {
			// Add door temp variable
			Door* doorTemp = new Door(this->_render_, this->_mapImageSprite_,
				item.value()["x"].get<int>(),
				item.value()["y"].get<int>());

			// Push into doors
			this->doors.push_back(doorTemp);
		}
	}
}

/**
 * This function used to logic
 * or maybe something
 */
void World::Update() {
	// Map sprite <Door>
	for (auto door : this->doors) {
		door->Update();
	}
}

/**
 * This function used to render the tiles
 */
void World::Render() {
	// Map <Array>
	for (auto item : this->_data_world_.items()) {
		// Check if the tile
		if (item.value()["type"].get<std::string>() == "tiles") {
			// Set size
			this->destination.w = item.value()["width"].get<int>();
			this->destination.h = item.value()["height"].get<int>();

			// Map <Array>(tiles)
			for (auto tile : item.value()["tiles"].items()) {
				// Set position
				this->destination.x = tile.value()["gridX"].get<int>() * this->destination.w;
				this->destination.y = tile.value()["gridY"].get<int>() * this->destination.h;

				// Render
				SDL_RenderCopy(this->_render_,
					this->_mapImageTexture_->textures[item.value()["IDTexture"].get<int>()].data,
					&this->_mapImageTexture_->textures[item.value()["IDTexture"].get<int>()].tiles
					[tile.value()["tileY"].get<int>()]
					[tile.value()["tileX"].get<int>()],
					&this->destination);
			}
		}
	}

	// Map sprite <Door>
	for (auto door : this->doors) {
		door->Render();
	}
}