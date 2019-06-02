#pragma once
#include <cstdint>

class Tetromino
{
public:
	struct Block
	{
		Block(uint32_t r = 0, uint32_t g = 0, uint32_t b = 0, int32_t relX = 0, int32_t relY = 0) : r(r), g(g), b(b), relX(relX), relY(relY)
		{
		}

		uint32_t r;
		uint32_t g;
		uint32_t b;
		int32_t relX;
		int32_t relY;
	};

	explicit Tetromino(uint32_t type);
	~Tetromino();

	static const Tetromino tetrominoes_[7];

	Block* blocks_;

	uint32_t x;
	uint32_t y;

private:
	Tetromino(Block* block);
};
