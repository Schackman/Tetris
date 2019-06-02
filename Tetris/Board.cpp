#include "Board.h"
#include <SDL2/SDL.h>
#include <random>
#include <iostream>


Board::Board()
{

	for (auto i = 0; i < ROWS; ++i)
	{
		for (auto j = 0; j < COLS; ++j)
		{
			board_[i][j] = {0, 0, 0, 0, 0};
		}
	}
}


Board::~Board()
{
}

void Board::input(SDL_Event ev)
{
	
}

void Board::update(uint32_t deltaTime)
{
	
}

void Board::render(Renderer* renderer) const
{
	SDL_Rect boardRect;
	boardRect.x = 0;
	boardRect.y = 0;
	boardRect.w = WIDTH;
	boardRect.h = HEIGTH;
	SDL_SetRenderDrawColor(renderer->getRenderer(), 100, 100, 100, 1);
	SDL_RenderFillRect(renderer->getRenderer(), &boardRect);

	SDL_Rect rect;
	for (auto row = 0; row < ROWS; ++row)
	{
		for (auto col = 0; col < COLS; ++col)
		{
			auto r = board_[row][col].r;
			auto g = board_[row][col].g;
			auto b = board_[row][col].b;
			rect.x = col * COL_WIDTH;
			rect.y = row * ROW_HEIGTH;
			rect.h = ROW_HEIGTH;
			rect.w = COL_WIDTH;

			SDL_SetRenderDrawColor(renderer->getRenderer(), r, g, b, 1);
			SDL_RenderFillRect(renderer->getRenderer(), &rect);

			if (!isCoordEmpty(row, col))
			{
				SDL_SetRenderDrawColor(renderer->getRenderer(), 160, 160, 160, 1);
				SDL_RenderDrawRect(renderer->getRenderer(), &rect);
			}
		}
	}
}

bool Board::isCoordEmpty(uint32_t row, uint32_t col) const
{
	auto r = board_[row][col].r;
	auto g = board_[row][col].g;
	auto b = board_[row][col].b;
	return r == 0 && g == 0 && b == 0;
}

bool Board::isCoordOnBoard(uint32_t row, uint32_t col) const
{
	return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}
