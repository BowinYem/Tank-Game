#ifndef SOUND_H
#define SOUND_H

#include<SDL_mixer.h>
#include <iostream>

class Sound{

private:

	Mix_Chunk* sound = NULL;
	
public:

	Sound(){};
	Sound(char* path);
	~Sound();
	void play();
	void load(char* path);

};

#endif