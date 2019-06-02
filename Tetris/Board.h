#pragma once
#include "Tetromino.h"
#include "Renderer.h"

class Renderer;

class Board
{
public:
	Board();
	~Board();

	const uint32_t WIDTH = 210;
	const uint32_t HEIGTH = 350;
	static const uint32_t COLS = 12;
	static const uint32_t ROWS = 20;
	const uint32_t COL_WIDTH = WIDTH / COLS;
	const uint32_t ROW_HEIGTH = HEIGTH / ROWS;

	void input(SDL_Event ev);
	void update(uint32_t deltaTime);
	void render(Renderer* renderer) const;
	void cleanup();

	bool isCoordEmpty(uint32_t row, uint32_t col) const;
	bool isCoordOnBoard(uint32_t row, uint32_t col) const;
	Tetromino::Block board_[ROWS][COLS];
};

