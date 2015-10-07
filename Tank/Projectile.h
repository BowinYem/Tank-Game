#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SDL.h>
#include "Texture.h"


class Projectile
{

protected:

	Texture* texture;
	int x;
	int y;
	int XVelocity;
	int YVelocity;

public:
	
	Projectile(SDL_Renderer* renderer, int x, int y, int XVelocity, int YVelocity, int spriteWidth, int spriteHeight);
	void accelerate();
	bool detectWallCollision();
	void render(SDL_Renderer* renderer);
	void destroyProjectile();
	SDL_Rect getDest();
	
};

#endif // !PROJECTILE_H
