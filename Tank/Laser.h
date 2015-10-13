#ifndef LASER_H
#define LASER_H
#include <SDL.h>
#include "Texture.h"
#include <vector>

class Laser{

protected:

	int x, y; //Where the laser "begins"
	int hitX, hitY; //These are for expanding the hitboxes
	int width; //width of the laser
	int run, rise;
	int maxLength;
	double angle;
	bool extended;

	SDL_Renderer* renderer;
	Texture* texture;
	vector<Texture*> hitboxes;

	bool hit(SDL_Rect object);

public:

	Laser(int x, int y, int run, int rise, int width, int maxLength, double angle, SDL_Renderer* renderer);
	void extend(); //extend the hitboxes
	void retract(); //retract the hitboxes
	void updateLaser(int x, int y, int run, int rise, double angle);
	void render();
	bool isExtended();

};

#endif