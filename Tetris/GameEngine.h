#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Timer.h"
#include "GameState.h"
#include <vector>


class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void run();
	
	Window* window;
	Renderer* renderer;

	const uint32_t TARGET_UPS;
	uint32_t TARGET_FPS;

	GameState* current_game_state;

private:
	void init();
	void input();
	void gameLoop();
	void sync();
	void cleanup();

	void update(uint32_t deltatime);
	void render();

	bool shouldClose;

	Timer* timer_;
};

