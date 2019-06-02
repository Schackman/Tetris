#include "SoundEngine.h"



SoundEngine::SoundEngine(): wav_lenth_(0), wav_buffer_(nullptr)
{
	SDL_Init(SDL_INIT_AUDIO);
	SDL_LoadWAV("resources/audio/Sparta_Whoosh_Down-ebbd3dac.wav", &wav_spec_, &wav_buffer_, &wav_lenth_);
	SDL_PauseAudio(0);
}


SoundEngine::~SoundEngine()
{
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
