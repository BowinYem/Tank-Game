#ifndef LASER_H
#define LASER_H
#include <SDL.h>
#include "Texture.h"
#include <vector>

class Laser{

protected:
	Texture* texture;
	vector<Texture*> hitboxes;
	vector<Texture*>::iterator iterator;
	bool hit(SDL_Rect object);
	int x, y; //Where the laser "begins"
	int hitX, hitY; //These are for expanding the hitboxes
	int width; //width of the laser
	int run, rise;
	int maxLength;
	double angle;

public:
	Laser(int x, int y, int run, int rise, int width, int maxLength, double angle, SDL_Renderer* renderer) : x(x), y(y), hitX(x), hitY(y),
		run(run), rise(rise), width(width), maxLength(maxLength)
	{
		texture = new Texture("projectile.png", renderer, SDL_Rect{ 0, 0, 20, 20 }, SDL_Rect{ x, y, width, maxLength });
		texture->setAngle(angle);
		iterator = hitboxes.begin();	
	}

	void extend(SDL_Renderer* renderer); //extend the hitboxes
	void retract(); //retract the hitboxes
	void updateLaser(int x, int y, int run, int rise, double angle);
	void render(SDL_Renderer* renderer);
};



#endif