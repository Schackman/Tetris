#pragma once
#include <SDL2/SDL.h>

class Window
{
public:
	Window();
	Window(uint32_t width, uint32_t height);
	~Window();

	void init();
	void update();
	void cleanup();

	SDL_Window* getWindow() const;

	uint32_t width;
	uint32_t height;

private:
	SDL_Window* sdl_window_;
};

