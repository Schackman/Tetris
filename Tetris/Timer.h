#pragma once
#include <cstdint>

#define SECOND 1000
class Timer
{
public:
	Timer();
	~Timer();

	void init();
	void update();
	uint32_t getElapsedTime();

	void updateUPSCounter();
	void updateFPSCounter();

	uint32_t getUPS() const;
	uint32_t getFPS() const;
	uint32_t getLastLoopTime() const;
	uint32_t getTime() const;

private:
	uint32_t ups_;
	uint32_t upsCounter_;
	uint32_t fps_;
	uint32_t fpsCounter_;
	uint32_t lastLoopTime_;
	uint32_t timeCounter_;
};

