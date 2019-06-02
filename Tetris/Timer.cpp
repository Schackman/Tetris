#include "Timer.h"
#include <SDL2/SDL.h>


Timer::Timer(): ups_(0), upsCounter_(0), fps_(0), fpsCounter_(0), lastLoopTime_(0), timeCounter_(0)
{
}


Timer::~Timer()
{
}

void Timer::init()
{
	lastLoopTime_ = SDL_GetTicks();
}


void Timer::update()
{
	if (timeCounter_ >= SECOND)
	{
		fps_ = fpsCounter_;
		fpsCounter_ = 0;

		ups_ = upsCounter_;
		upsCounter_ = 0;

		timeCounter_ -= SECOND;
	}
}


uint32_t Timer::getElapsedTime()
{
	auto time = SDL_GetTicks();
	auto elapsedTime = time - lastLoopTime_;
	lastLoopTime_ = time;
	timeCounter_ += elapsedTime;
	return elapsedTime;
}

uint32_t Timer::getUPS() const
{
	return ups_;
}

uint32_t Timer::getFPS() const
{
	return fps_;
}

uint32_t Timer::getLastLoopTime() const
{
	return lastLoopTime_;
}

uint32_t Timer::getTime() const
{
	return SDL_GetTicks();
}


void Timer::updateFPSCounter()
{
	fpsCounter_++;
}

void Timer::updateUPSCounter()
{
	upsCounter_++;
}
