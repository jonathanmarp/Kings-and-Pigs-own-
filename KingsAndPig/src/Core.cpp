// Include header <Self>
#include "../include/Core.h"

// Include header <SDL2>
#include <SDL.h>

// Constructor
Core::Core(SDL_Window* window, SDL_Renderer* render) 
	: _window_(window), _render_(render) {}

/**
 * This function used for to program run
 * On this class
 */
void Core::SetProgramRun(bool into) {
	// Set data
	this->_program_run_ = into;
}

/**
 * This function used to get window
 * On this class
 */
SDL_Window* Core::GetWindow() {
	// return data
	return this->_window_;
}

/**
 * This function used to get render
 * On this class
 */
SDL_Renderer* Core::GetRender() {
	// return data
	return this->_render_;
}

/**
 * This function used for to program run
 * On this class
 */
const bool& Core::IsProgramRun() const {
	// return data
	return this->_program_run_;
}

/**
 * This function used to get FPS
 * On this class
 */
const uint8_t& Core::HowManyFPS() const {
	// return data
	return this->_fps_;
}

/**
 * This function used to get Event
 * On this class
 */
SDL_Event* Core::GetEvent() {
	// return data
	return &this->_event_;
}