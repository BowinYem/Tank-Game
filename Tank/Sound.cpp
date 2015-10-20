#include "Sound.h"

Sound::Sound(char* path)
{
	sound = Mix_LoadWAV(path);

	if (sound == NULL)
	{
		std::cout << "Mix_LoadWAV has Failed";
	}
}

Sound::~Sound()
{
	Mix_FreeChunk(sound);
	sound = NULL;
}

void Sound::play()
{
	Mix_PlayChannel(-1, sound, 0);
}

void Sound::load(char* path)
{
	Mix_FreeChunk(sound);
	sound = NULL;
	sound = Mix_LoadWAV(path);
}
