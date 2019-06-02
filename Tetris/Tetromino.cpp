#include "Tetromino.h"


Tetromino::Tetromino(Block block[4]):blocks_(block), x(5), y(0){}

Tetromino::Tetromino(uint32_t type): blocks_(new Block[4]), x(5), y(0)
{
	for (int i = 0; i < 4; ++i)
	{
		blocks_[i] = tetrominoes_[type].blocks_[i];
	}
}


Tetromino::~Tetromino()
{
	delete[] blocks_;
}

const Tetromino Tetromino::tetrominoes_[7] = {
	Tetromino(new Block[4]{Block(45, 223, 255, 0, 0),Block(45, 223, 255, 0, 1),Block(45, 223, 255, 0, 2) ,Block(45, 223, 255, 0, 3)}), // Straight tetromino
	Tetromino(new Block[4]{Block{240, 240, 20, 0, 0} , Block{240, 240, 20, 0, 1} , Block{240, 240, 20, 1, 0} , Block{240, 240, 20, 1, 1}}), // Square tetromino
	Tetromino(new Block[4]{Block{255, 0, 255, 0, 0},Block{255, 0, 255, 0, 1} ,Block{255, 0, 255, 1, 1} ,Block{255, 0, 255, -1, 1}}), // T-tetromino
	Tetromino(new Block[4]{Block{0, 0, 255, 0, 0}, Block{0, 0, 255, -1, 0}, Block{0, 0, 255, 0, 1}, Block{0, 0, 255, 0, 2}}), // J-tetromino
	Tetromino(new Block[4]{Block{255, 170, 0, 0, 0}, Block{255, 170, 0, 1, 0}, Block{255, 170, 0, 0, 1}, Block{255, 170, 0, 0, 2}}), // L-tetromino
	Tetromino(new Block[4]{Block{0, 255, 0, 0, 0}, Block{0, 255, 0, -1, 0}, Block{0, 255, 0, 0, 1}, Block{0, 255, 0, 1, 1}}), // Z-tetromino
	Tetromino(new Block[4]{Block{255, 0, 0, 0, 0}, Block{255, 0, 0, 1, 0}, Block{255, 0, 0, 0, 1}, Block{255, 0, 0, -1, 1}}) // S-tetromino
};
