#include "Tetris.h"
#include <iostream>
#include <random>

Tetris::Tetris(): moveDirection(0), shouldRotate(false), shouldDrop(false), shouldSpeedUp(false), timestep_(1000), timeCounter(0), level(1)
{
	board_ = new Board;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 6);
	tetromino_ = new Tetromino(uni(rng));
	next_tetromino_ = new Tetromino(uni(rng));
}

Tetris::~Tetris()
{
	delete board_;
}

void Tetris::init()
{
}

void Tetris::input(SDL_Event ev)
{
	switch (ev.type)
	{
		case SDL_KEYDOWN:
			if (ev.key.keysym.sym == SDLK_LEFT) moveDirection = -1;
			else if (ev.key.keysym.sym == SDLK_RIGHT) moveDirection = 1;
			else if (ev.key.keysym.sym == SDLK_SPACE) shouldDrop = true;
			else if (ev.key.keysym.sym == SDLK_DOWN) shouldSpeedUp = true;
			else if (ev.key.keysym.sym == SDLK_UP) shouldRotate = true;
			if (ev.key.keysym.sym == SDLK_p) pauze();
			else if (ev.key.keysym.sym == SDLK_RETURN) resume();
			break;
	}
}

void Tetris::update(uint32_t deltaTime)
{
	if (isPauzed) return;

	// remove tetromino from board
	hideTetromino();
	// Move tetromino if possible
	moveTetromino();
	// Rotate tetromino if possible
	rotateTetromino();
	// Drop tetromino if possible
	dropTetromino();
	// Place tetromino on board
	showTetromino();

	// check if enough time has passed for fall
	uint32_t timestep = timestep_ - shouldSpeedUp * timestep_ / 1.1 - (level-1) * 10;
	shouldSpeedUp = false;
	if (timeCounter < timestep)
	{
		timeCounter += deltaTime;
		return;
	}
	// remove tetromino from board
	hideTetromino();
	// Get next tetromino if current can't fall anymore
	if (!canTetrominoFall())
	{
		showTetromino();
		removeRows();
		if (!canPlaceNextTetromino())
		{
			std::cout << "Game Over" << std::endl;
			pauze();
		}
		else
		{
			getNextTetromino();
			return;
		}
	}
	else
	{
		// check if tetromino can fall
		fallTetromino();
	}

	// Place tetromino on board
	showTetromino();

	timeCounter = 0;
}

void Tetris::hideTetromino()
{
	for (auto i = 0; i < 4; ++i)
	{
		board_->board_[tetromino_->blocks_[i].relY + tetromino_->y][tetromino_->blocks_[i].relX + tetromino_->x] = Tetromino::Block(0, 0, 0);
	}
}

void Tetris::showTetromino()
{
	for (auto i = 0; i < 4; ++i)
	{
		board_->board_[tetromino_->blocks_[i].relY + tetromino_->y][tetromino_->blocks_[i].relX + tetromino_->x] = tetromino_->blocks_[i];
	}
}

bool Tetris::moveTetromino()
{
	// check if tetromino can move in requested direction
	for (int i = 0; i < 4; ++i)
	{
		auto xTemp = tetromino_->x + tetromino_->blocks_[i].relX + moveDirection;
		auto yTemp = tetromino_->y + tetromino_->blocks_[i].relY;
		if (!(board_->isCoordOnBoard(yTemp, xTemp) && board_->isCoordEmpty(yTemp, xTemp)))
		{
			return false;
		}
	}
	// Move tetromino
	tetromino_->x += moveDirection;
	moveDirection = 0;
	return true;
}

bool Tetris::rotateTetromino()
{
	if (!shouldRotate) return false;
	shouldRotate = false;
	// Check if tetromino can rotate
	for (int i = 0; i < 4; ++i)
	{
		auto xTemp = tetromino_->x - tetromino_->blocks_[i].relY;
		auto yTemp = tetromino_->y + tetromino_->blocks_[i].relX;
		if (!(board_->isCoordOnBoard(yTemp, xTemp) && board_->isCoordEmpty(yTemp, xTemp)))
		{
			return false;
		}
	}

	// Rotate tetromino
	for (int i = 0; i < 4; ++i)
	{
		auto temp = tetromino_->blocks_[i].relX;
		tetromino_->blocks_[i].relX = -tetromino_->blocks_[i].relY;
		tetromino_->blocks_[i].relY = temp;
	}
	return true;
}

bool Tetris::canTetrominoFall() const
{
	// Check if tetromino can move
	for (int i = 0; i < 4; ++i)
	{
		auto xTemp = tetromino_->x + tetromino_->blocks_[i].relX;
		auto yTemp = tetromino_->y + tetromino_->blocks_[i].relY + 1;
		if (!(board_->isCoordOnBoard(yTemp, xTemp) && board_->isCoordEmpty(yTemp, xTemp)))
		{
			return false;
		}
	}
	return true;
}

void Tetris::fallTetromino() const
{
	// Let tetromino fall
	tetromino_->y++;
}

void Tetris::dropTetromino()
{
	if (shouldDrop)
	{
		while (canTetrominoFall())
		{
			fallTetromino();
		}
	}
	shouldDrop = false;
}

void Tetris::getNextTetromino()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 6);

	tetromino_ = next_tetromino_;
	auto index = uni(rng);
	next_tetromino_ = new Tetromino(index);
}

void Tetris::removeRows()
{
	for (int i = Board::ROWS - 1; i >= 0; --i)
	{
		bool shouldRemoveRow = true;
		for (int j = 0; j < Board::COLS; ++j)
		{
			if (board_->isCoordEmpty(i, j))
				shouldRemoveRow = false;
		}
		if (shouldRemoveRow)
		{
			for (int j = 0; j < Board::COLS; ++j) board_->board_[i][j] = Tetromino::Block();
			std::cout << ++level << std::endl;
			dropRows();
		}
	}
}

void Tetris::dropRows()
{
	for (int i = Board::ROWS - 1; i >= 0; --i)
	{
		for (int j = 0; j < Board::COLS; ++j)
		{
			if (!board_->isCoordEmpty(i, j))
			{
				if (board_->isCoordOnBoard(i + 1, j) && board_->isCoordEmpty(i + 1, j))
				{
					board_->board_[i + 1][j] = board_->board_[i][j];
					board_->board_[i][j] = Tetromino::Block();
					i++;
				}
			}
		}
	}
	removeRows();
}

bool Tetris::canPlaceNextTetromino() const
{
	for (int i = 0; i < 4; ++i)
	{
		auto xTemp = next_tetromino_->x + next_tetromino_->blocks_[i].relX;
		auto yTemp = next_tetromino_->y + next_tetromino_->blocks_[i].relY;
		if (!(board_->isCoordOnBoard(yTemp, xTemp) && board_->isCoordEmpty(yTemp, xTemp)))
		{
			return false;
		}
	}
	return true;
}


void Tetris::render(Renderer* renderer)
{
	board_->render(renderer);
}

void Tetris::pauze()
{
	isPauzed = true;
}

void Tetris::resume()
{
	isPauzed = false;
}

void Tetris::cleanup()
{
}

Tetris& Tetris::getInstance()
{
	static Tetris tetris;
	return tetris;
}
