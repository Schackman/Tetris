#include "Window.h"



Window::Window(): width(500), height(640), sdl_window_(nullptr)
{
}

Window::Window(uint32_t width, uint32_t height): width(width), height(height), sdl_window_(nullptr)
{
}


Window::~Window()
{
	
}

void Window::init()
{
	SDL_Init(SDL_INIT_VIDEO);
	sdl_window_ = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
}

void Window::update()
{
	
}

void Window::cleanup()
{
	SDL_DestroyWindow(sdl_window_);
	SDL_VideoQuit();
}


SDL_Window* Window::getWindow() const
{
	return sdl_window_;
}


