#pragma once
#include "GameState.h"
#include "Board.h"

class Tetris : public GameState
{
public:
	void init() override;
	void cleanup() override;
	void input(SDL_Event ev) override;
	void update(uint32_t deltaTime) override;
	void render(Renderer* renderer) override;
	void pauze() override;
	void resume() override;

	static Tetris& getInstance();
	
private:
	Tetris();
	Tetris(Tetris const&) = delete;
	void operator=(Tetris const&) = delete;

	Board* board_;
	Tetromino* tetromino_;
	Tetromino* next_tetromino_;

	int8_t moveDirection;

	bool shouldRotate;
	bool shouldDrop;
	bool shouldSpeedUp;

	uint32_t timestep_;
	uint32_t timeCounter;

	uint32_t level;

	void hideTetromino();
	void showTetromino();
	bool moveTetromino();
	void dropTetromino();
	bool rotateTetromino();
	void fallTetromino() const;
	bool canTetrominoFall() const;
	void removeRows();
	void dropRows();

	bool canPlaceNextTetromino() const;
	void getNextTetromino();

protected:	
	~Tetris();
};
