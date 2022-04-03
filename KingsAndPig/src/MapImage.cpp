// Include header <Self>
#include "../include/MapImage.h"

// Include header <C++>
#include <iostream>
#include <fstream>

// Include header <Important>
#include "../include/File.h"

// Include header <SDL2>
#include <SDL_image.h>

// Constructor
MapImage::MapImage(SDL_Renderer* render, std::string path)
	: pathToTexture(path), _render_(render) {
	// Check file is exist
	if (File::IsExist(this->pathToTexture)) {
		// If exist
		// Get file
		std::ifstream _data_;

		// Open
		_data_.open(this->pathToTexture);

		// Convert into 
		_data_ >> _data_json_;

		// Close
		_data_.close();
	}
	else {
		// Show error
		std::cout << "Error texture: " << this->pathToTexture << std::endl;

		// Exit
		exit(1);
	}

	// Cal start
	this->Start();
}

/**
 * This function will call when intialize
 * The constructor
 */
void MapImage::Start() {
	// Map
	for (auto item : this->_data_json_.items()) {
		// Setup
		SDL_Surface* _image_;
		SDL_RWops* _rwop_;

		// Get image
		_rwop_ = SDL_RWFromFile(item.value()["assets"].get<std::string>().c_str(), "rb");
		_image_ = IMG_LoadPNG_RW(_rwop_);

		// Check
		if (!_image_) {
			// Show message error
			std::cout << "Error: " << IMG_GetError() << std::endl;

			// exit
			exit(1);
		}

		// Setup MapImageStruct
		MapImageStruct _temp_data_;

		// Texture
		_temp_data_.data = SDL_CreateTextureFromSurface(this->_render_,
			_image_);

		// Setup variable
		uint8_t widthImage = item.value()["width"].get<int>();
		uint8_t heightImage = item.value()["height"].get<int>();

		// Make tiles rect
		// <Vertical>
		for (uint8_t vertical = 0; vertical < uint8_t(_image_->h / heightImage); vertical++) {
			// <Setup>
			std::vector<SDL_Rect> _tiles_;

			// <Horizontal>
			for (uint8_t horizontal = 0; horizontal <
				uint8_t(_image_->w / widthImage); horizontal++) {
				// Setup rect
				SDL_Rect _temp_rect_;

				// Size tile
				_temp_rect_.w = widthImage;
				_temp_rect_.h = heightImage;

				// Position tile
				_temp_rect_.x = horizontal * widthImage;
				_temp_rect_.y = vertical * heightImage;

				// Push into temp data
				_tiles_.push_back(_temp_rect_);
			}

			// <Push>
			_temp_data_.tiles.push_back(_tiles_);
		}

		// Push into textures
		this->textures.push_back(_temp_data_);

		// destroy
		SDL_FreeSurface(_image_);
		SDL_RWclose(_rwop_);
	}
}