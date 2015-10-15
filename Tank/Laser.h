#ifndef LASER_H
#define LASER_H
#include <SDL.h>
#include "Texture.h"
#include <vector>

class Laser{

protected:

	//Dimensions of the laser sprite source
	const int SPRITE_WIDTH = 20;
	const int SPRITE_LENGTH = 20;

	int x, y; //Where the laser "begins"
	int hitX, hitY; //These are for enlongating the hitboxes
	int bitWidth, bitLength; //dimensions for each piece of "laser"
	int totalLength; //the total number of "laser pieces" in our overall laser
	int run, rise;
	bool extended;

	SDL_Renderer* renderer;
	vector<Texture*> laserTextures;

public:

	Laser(int x, int y, int run, int rise, int bitWidth, int bitLength, int totalLength, SDL_Renderer* renderer);
	void extend(); 
	void retract(); 
	void updateLaser(int x, int y, int run, int rise);
	bool isExtended();
	bool hit(SDL_Rect object);
	void increaseBitWidth(int x);
	void increaseBitLength(int x);
	void render();

};

#endif