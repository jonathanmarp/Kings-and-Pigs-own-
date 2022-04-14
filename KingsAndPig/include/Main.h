#ifndef MAIN_H
#define MAIN_H

// Include header <C++>
#include <string>
#include <future>

// Include header <Important>
#include "Core.h"
#include "MapImage.h"
#include "World.h"

// Include header <Third Party>
#include <nlohmann/json.hpp>

class Main {
private:
	// This variable used for vital of program
	Core* core = nullptr;

	// This used for limit frame
	uint32_t startTicks = 0;

	// This variable used to settings
	nlohmann::json settingsWindow;

	// Path settings
	std::string windowSettings = "../Core/window.json";

	// Size window
	struct {
		int width; // width
		int height; // height
	} sizeWindow;

	// Grid color
	SDL_Color gridColor = { 0x61, 0x5f, 0x87 };

	// This function used for texture
	MapImage* mapImageTexture = nullptr;
	nlohmann::json jsonSprite;

	// This variable will save our world and information
	uint8_t levelWorld = 0;
	std::vector<World> worlds;

	// This variable used for async
	std::future<SDL_Window*> window_init;
public:
	// Constructor
	Main();

	// Deconstructor
	~Main();

private:
	// This function used for first time
	inline void Start();

	// This function used for handle event
	inline void Event();

	// This function used for logic
	inline void Update();

	// This function used for render
	inline void Render();
};

#endif // MAIN_H