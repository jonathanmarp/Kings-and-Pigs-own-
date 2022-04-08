// Include header <Self>
#include "../include/World.h"

// Include header <C++>
#include <iostream>

// Constructor
World::World(SDL_Renderer* render, nlohmann::json& data, 
	MapImage* mapImageTexture, nlohmann::json& dataSprite)
	: _render_(render), _data_world_(data), 
	  _mapImageTexture_(mapImageTexture) {
	// Map <Array>
	std::for_each(dataSprite.items().begin(), dataSprite.items().end(), [&](auto& item) {
		// Make variable
		SpriteImages _temp_;

		// <Ref>
		nlohmann::json& data = item.value();

		// Set name
		_temp_.name = item.value()["name"].get<std::string>();

		// Intialize map image
		_temp_.mapImageSprite = new MapImage(this->_render_,
			std::string("../Core/" + data["texture"].get<std::string>()));

		// Push into <spriteTexture>
		spriteTexture.push_back(_temp_);
	});

	// Map <Array>
	std::for_each(this->_data_world_.items().begin(), 
		this->_data_world_.items().end(), [&](auto& item) {
		// Setup variable for checking types
		std::string types = item.value()["type"].get<std::string>();

		// Check if the tile
		if (types == "door") [[likely]] {
			// Add door temp variable
			Door* doorTemp = new Door(this->_render_, this->GetTexture("door"),
				item.value()["x"].get<int>(),
				item.value()["y"].get<int>());

			// Push into doors
			this->doors.push_back(doorTemp);
		}
	});
}

/**
 * This function used for get data texture
 */
MapImage* World::GetTexture(std::string name) {
	// Map <Array>
	for (auto& item : this->spriteTexture) {
		// Check name is exist or not
		if (item.name == name) [[likely]] {
			// return data
			return item.mapImageSprite;
		}
	}
	
	// return first data if doesn't exist
	return this->spriteTexture[0].mapImageSprite;
}

/**
 * This function used to logic
 * or maybe something
 */
void World::Update() {
	// Map sprite <Door>
	std::for_each(this->doors.begin(), this->doors.end(), [](auto& door) {
		door->Update();
	});
}

/**
 * This function used to render the tiles
 */
void World::Render() {
	// Map <Array>
	std::for_each(this->_data_world_.items().begin(),
		this->_data_world_.items().end(), [&](auto& item) {
		// Check if the tile
		if (item.value()["type"].get<std::string>() == "tiles") [[likely]] {
			// Set size
			this->destination.w = item.value()["width"].get<int>();
			this->destination.h = item.value()["height"].get<int>();

			// Map <Array>(tiles)
			for (auto &tile : item.value()["tiles"].items()) {
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
	});

	// Map sprite <Door>
	std::for_each(this->doors.begin(), this->doors.end(), [](auto& door) {
		door->Render();
	});
}