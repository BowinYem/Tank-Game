#include "Meteor.h"


Meteor::Meteor(SDL_Renderer* renderer, int x, int y, int XVelocity, int YVelocity, int spriteWidth, int spriteHeight) :
Projectile(renderer, x, y, XVelocity, YVelocity, spriteWidth, spriteHeight)
{
	health = spriteWidth;
	
}

void Meteor::decreaseHealth(int damage)
{
	health -= damage;
}

int Meteor::getHealth()
{
	return health;
}