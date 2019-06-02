#pragma once
#include <SDL2/SDL.h>

class SoundEngine
{
public:
	SoundEngine();
	~SoundEngine();

private:
	SDL_AudioSpec wav_spec_;
	uint32_t wav_lenth_;
	uint8_t* wav_buffer_;
};

