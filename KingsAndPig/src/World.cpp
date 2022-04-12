// Include header <Self>
#include "../include/World.h"

// Include header important
#include "../include/Rigidbody.h"

// Include header <C++>
#include <iostream>

// Constructor
World::World(Core* pCore, nlohmann::json& data,
	MapImage* mapImageTexture, nlohmann::json& dataSprite)
	: core(pCore), _data_world_(data), 
	  _mapImageTexture_(mapImageTexture) {
	// Intialize world
	this->world = new b2World(b2Vec2(0.0f, 10.0f));

	// Map <Array>
	std::for_each(dataSprite.items().begin(), dataSprite.items().end(), [&](auto& item) {
		// Make variable
		SpriteImages _temp_;

		// <Ref>
		nlohmann::json& data = item.value();

		// Set name
		_temp_.name = item.value()["name"].get<std::string>();

		// Intialize map image
		_temp_.mapImageSprite = new MapImage(this->core->GetRender(),
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
		if (types == "tiles") [[likely]] {
			// Check if collider tiles
			if (item.value()["colider"].get<int>() == 1) {
				// Set size
				float width = item.value()["width"].get<float>();
				float height = item.value()["height"].get<float>();

				// Map <Array>(tiles)
				for (auto& tile : item.value()["tiles"].items()) {
					// Set position
					float x = tile.value()["gridX"].get<float>() * width;
					float y = tile.value()["gridY"].get<float>() * height;

					// Make rigidbody
					Rigidbody _temp_tiles_;
					_temp_tiles_.RigidBodyGroundInit(this->world, x, y, width, height);
				}
			}
		} 
		else if (types == "door") [[likely]] {
			// Add door temp variable
			Door* doorTemp = new Door(this->core->GetRender(), this->GetTexture("door"),
				item.value()["x"].get<int>(),
				item.value()["y"].get<int>());

			// Push into doors
			this->doors.push_back(doorTemp);
		}
		else if (types == "avatar") [[likely]] {
			// Add door temp variable
			Avatar* avatarTemp = new Avatar(this->core, this->GetTexture("avatar"),
				this->world,
				item.value()["x"].get<int>(),
				item.value()["y"].get<int>());

			// Push into doors
			this->avatars.push_back(avatarTemp);
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
	// Update step
	this->world->Step(this->timeStep, this->velocityIterations, this->positionIterations);

	// Map sprite <Door>
	std::for_each(this->doors.begin(), this->doors.end(), [](auto& door) {
		door->Update();
	});

	// Map sprite <Avatar>
	std::for_each(this->avatars.begin(), this->avatars.end(), [](auto& avatar) {
		avatar->Update();
	});
}

/**
 * This function used to handle
 * Event
 */
void World::Event() {
	// Map sprite <Avatar>
	std::for_each(this->avatars.begin(), this->avatars.end(), [](auto& avatar) {
		avatar->Event();
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
				SDL_RenderCopy(this->core->GetRender(),
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

	// Map sprite <Avatar>
	std::for_each(this->avatars.begin(), this->avatars.end(), [](auto& avatar) {
		avatar->Render();
	});
}