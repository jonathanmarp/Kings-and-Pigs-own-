#ifndef CORE_H
#define CORE_H

// Include header <SDL2>
#include <SDL.h>

class Core {
private:
	/**
	 * Program run for know
	 * The program should run or stop
	 */
	bool _program_run_ = true;

	/**
	 * For know about
	 * Frame per seconds
	 */
	uint8_t _fps_ = 60;

	/**
	 * This window will refrench on constructor
	 */
	SDL_Window* _window_ = nullptr;

	/**
	 * This render will refrench on constructor
	 */
	SDL_Renderer* _render_ = nullptr;

	/**
	 * This event for get event from window
	 */
	SDL_Event _event_ = SDL_Event();
public:
	// Constructor
	Core(SDL_Window* window, SDL_Renderer* render);

public:
	/**
	 * This function used for set program run
	 * On this class
	 */
	void SetProgramRun(bool into);

public:
	/**
	 * This function used to get window
	 * On this class
	 */
	SDL_Window* GetWindow();

	/**
	 * This function used to get render
	 * On this class
	 */
	SDL_Renderer* GetRender();

	/**
	 * This function used to get program run
	 * On this class
	 */
	bool& IsProgramRun();

	/**
	 * This function used to get FPS
	 * On this class
	 */
	uint8_t& HowManyFPS();

	/**
	 * This function used to get Event
	 * On this class
	 */
	SDL_Event* GetEvent();
};

#endif // CORE_H