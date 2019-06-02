#pragma once
#include <SDL2/SDL.h>
#include "Window.h"

class Renderer
{
public:
	explicit Renderer(Window* window);
	~Renderer();

	void init();
	void render() const;
	void clear() const;
	void cleanup();

	SDL_Renderer* getRenderer() const;
	Window* getWindow() const;

private:
	Window* window_;
	SDL_Renderer* sdl_renderer_;
};

