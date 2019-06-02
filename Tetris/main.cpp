#include <SDL2/SDL.h>
#include "GameEngine.h"
#include "Tetris.h"

int main(int argc, char** args)
{
	GameEngine game_engine;
	GameState* state = &Tetris::getInstance();
	state->init();
	game_engine.current_game_state = state;
	game_engine.run();
	return 0;
}
