#pragma once

#include <cstdint>
#include "Renderer.h"

class GameState
{
public:
	virtual ~GameState() = default;
	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void input(SDL_Event ev) = 0;
	virtual void update(uint32_t deltaTime) = 0;
	virtual void render(Renderer* renderer) = 0;

	virtual void pauze() = 0;
	virtual void resume() = 0;

protected:
	GameState() = default;
	bool isPauzed;
};
