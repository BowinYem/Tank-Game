#ifndef METEOR_H
#define METEOR_H
#include <SDL.h>
#include "Projectile.h"

class Meteor : public Projectile
{
	int health;
	int damage;

public:
	Meteor(SDL_Renderer* renderer, int x, int y, int XVelocity, int YVelocity, int spriteWidth, int spriteHeight);
	void decreaseHealth(int damage);
	int getHealth();
};


#endif