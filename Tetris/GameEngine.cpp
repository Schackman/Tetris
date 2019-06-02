#include "GameEngine.h"
#include <thread>


GameEngine::GameEngine(): TARGET_UPS(20), TARGET_FPS(60), current_game_state(nullptr), shouldClose(false)
{
	window = new Window(600, 800);
	renderer = new Renderer(window);
	timer_ = new Timer;
}


GameEngine::~GameEngine()
{
	delete renderer;
	delete window;
}


void GameEngine::run()
{
	init();
	gameLoop();
	cleanup();
}

void GameEngine::init()
{
	SDL_Init(SDL_INIT_EVENTS);
	window->init();
	renderer->init();
	timer_->init();
}

void GameEngine::gameLoop()
{
	auto deltaTime = SECOND / TARGET_UPS; //time between updates in milliseconds
	uint32_t timeCounter = 0;

	while (!shouldClose)
	{
		timeCounter += timer_->getElapsedTime();

		input();
		while (timeCounter >= deltaTime)
		{
			update(deltaTime);
			timeCounter -= deltaTime;
			timer_->updateUPSCounter();
		}

		render();
		//std::cout << timer_->getUPS() << " UPS | " << timer_->getFPS() << " FPS" << std::endl;
		timer_->updateFPSCounter();

		sync();

		timer_->update();
	}
}

void GameEngine::input()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_QUIT:
				shouldClose = true;
				break;
			default:
				current_game_state->input(ev);
		}
	}
}

void GameEngine::update(uint32_t deltaTime)
{
	current_game_state->update(deltaTime);
}

void GameEngine::render()
{
	renderer->clear();
	current_game_state->render(renderer);
	renderer->render();
}

void GameEngine::sync()
{
	auto loopslot = SECOND / TARGET_FPS;
	auto endTime = timer_->getLastLoopTime() + loopslot;
	while (timer_->getTime() < endTime)
	{
		std::this_thread::yield();
	}
}


void GameEngine::cleanup()
{
	renderer->cleanup();
	window->cleanup();
	SDL_Quit();
}
