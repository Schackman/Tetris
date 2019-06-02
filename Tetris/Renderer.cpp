#include "Renderer.h"


Renderer::Renderer(Window* window) : window_(window), sdl_renderer_(nullptr)
{
}


Renderer::~Renderer()
{
	
}

void Renderer::init()
{
	sdl_renderer_ = SDL_CreateRenderer(window_->getWindow(), 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Renderer::render() const
{
	SDL_RenderPresent(sdl_renderer_);
}

void Renderer::clear() const
{
	SDL_SetRenderDrawColor(sdl_renderer_, 0, 0, 0, 1);
	SDL_RenderClear(sdl_renderer_);
}


void Renderer::cleanup()
{
	SDL_DestroyRenderer(sdl_renderer_);
	sdl_renderer_ = nullptr;
}

SDL_Renderer* Renderer::getRenderer() const
{
	return sdl_renderer_;
}

Window* Renderer::getWindow() const
{
	return window_;
}

