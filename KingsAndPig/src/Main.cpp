// Include header <Self>
#include "../include/Main.h"

// Include header <SDL2>
#include <SDL.h>
#include <SDL_image.h>

// Include header <C++>
#include <iostream>
#include <fstream>

// Include header <Draw>
// <Line>
#include "Line.h"

// Include header <Important>
// <File>
#include "../include/File.h"

// <Json>
#include "../include/Json.h"

// Include header <C++>
#include <filesystem>

// Constructor
Main::Main() {
	// Set SDL2 into ready
	SDL_SetMainReady();

	/** 
	 * Init SDL2{Timer, Video, Events}
	 * And check intialize has been successfull
	 */
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) [[unlikely]] {
		// Show error message
		std::cout << "Error: " << SDL_GetError() << std::endl;
		return;
	}

	/**
	 * load support for the  PNG image formats
	 */
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) [[unlikely]] {
		// Show error message
		std::cout << "Error: " << IMG_GetError() << std::endl;
	}

	// Start <Class>
	this->Start();

	// Start <Looping>
	while (core->IsProgramRun()) [[likely]] {
		// Get ticks for first loop
		this->startTicks = SDL_GetTicks();

		// Get event
		while (SDL_PollEvent(this->core->GetEvent())) [[likely]] {
			// Call handle event
			this->Event();
		}

		// Logic section
		// Call update function
		this->Update();

		// Render Section
		// Call render function
		this->Render();

		// Proccess frame per seconds
		if ((1000 / core->HowManyFPS()) > (SDL_GetTicks() - this->startTicks)) {
			SDL_Delay(1000 / core->HowManyFPS() - (SDL_GetTicks() - this->startTicks));
		}
	}
}

// Deconstructor
Main::~Main() {
	// Free pointer
	delete this->mapImageTexture;

	// Img Quit
	IMG_Quit();

	// SDL Quit
	SDL_Quit();
}

// This function used for first time
void Main::Start() {
	// Setup
	Json::GetData(this->windowSettings, &this->settingsWindow);
	
	// Intialize window
	SDL_Window* window = SDL_CreateWindow("Kings and Pigs",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		this->settingsWindow["width"].get<int>(), this->settingsWindow["height"].get<int>(), 
		0);

	// Settings
	// <Resize>
	SDL_SetWindowResizable(window, 
		this->settingsWindow["resizable"].get<SDL_bool>());
	
	// <Minimal>
	SDL_SetWindowMinimumSize(window, 
		this->settingsWindow["minWidth"].get<int>(), 
		this->settingsWindow["minHeight"].get<int>());

	// Setup for render
	Uint32 flagsRender = SDL_RENDERER_PRESENTVSYNC;

	// If using accelerate
	if (this->settingsWindow["accelerate"].get<int>() > 0) [[likely]] {
		// Add accelerate flags
		flagsRender |= SDL_RENDERER_ACCELERATED;
	}

	// Intialize Render
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, flagsRender);

	// Check window and render have error
	if (!window || !render) [[unlikely]] {
		// Show error message
		std::cout << "Error: " << SDL_GetError() << std::endl;
	}

	// Intialize
	this->core = new Core(window, render);

	// Intialize map image
	this->mapImageTexture = new MapImage(this->core->GetRender(), 
		std::string("../Core/" + this->settingsWindow["textureWorld"].get<std::string>()));
	
	// Get Data
	Json::GetData("../Core/" + this->settingsWindow["textureSprite"].get<std::string>(), 
		&this->jsonSprite);

	// Add world
	for (auto list : std::filesystem::directory_iterator("../Core/level")) {
		// Setup
		std::string tempWorldSettings = list.path().string();
		nlohmann::json tempSettingsWorld;

		// Get Data
		Json::GetData(tempWorldSettings, &tempSettingsWorld);

		// Setup world
		World tempWorld = World(this->core, tempSettingsWorld,
			this->mapImageTexture, this->jsonSprite);

		// <Push> into world
		this->worlds.push_back(tempWorld);
	}
}

// This function used for handle event
void Main::Event() {
	// Call event on <World>
	this->worlds[this->levelWorld].Event();

	// Switch
	switch (this->core->GetEvent()->type) {
		// If SDL Request quit
		[[unlikely]] case SDL_QUIT: {
			// Quit
			this->core->SetProgramRun(false);
		} break;

			// If SDL Window event
		[[unlikely]] case SDL_WINDOWEVENT: {
			// Get event
			const uint32_t DT = this->core->GetEvent()->window.type;

			// Check if close request
			if (DT == SDL_WINDOWEVENT_CLOSE) {
				// Quit
				this->core->SetProgramRun(false);
			}
		} break;
	}
}

// This function used for logic
void Main::Update() {
	// Map worlds
	std::for_each(this->worlds.begin(), this->worlds.end(), [](auto& world) {
		// Update
		world.Update();
	});
}

// This function used for render
void Main::Render() {
	// Set render color
	SDL_SetRenderDrawColor(this->core->GetRender(), 0x3f, 0x38, 0x51, 0);

	// Clear window
	SDL_RenderClear(this->core->GetRender());

	// Check window if using grid
	if (this->settingsWindow["grid"].get<int>() == 1) {
		// Make grid
		// Get size
		SDL_GetWindowSize(this->core->GetWindow(),
			&this->sizeWindow.width, &this->sizeWindow.height);

		// Horizontal
		for (int i = 1; i < int(this->sizeWindow.width / 32) + 1; i++) {
			// Draw <Line>
			Line::Draw(this->core->GetRender(), 1, this->gridColor,
				LineType::ToRight, 32 * i, 0, 32 * i, this->sizeWindow.height);
		}

		// Vertical
		for (int i = 1; i < int(this->sizeWindow.height / 32) + 1; i++) {
			// Draw <Line>
			Line::Draw(this->core->GetRender(), 1, this->gridColor,
				LineType::ToDown, 0, 32 * i, this->sizeWindow.width, 32 * i);
		}
	}

	// Render
	this->worlds[levelWorld].Render();

	// Present window
	SDL_RenderPresent(this->core->GetRender());
}