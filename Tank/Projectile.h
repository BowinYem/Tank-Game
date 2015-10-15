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
	~Projectile();
	void accelerate();
	bool detectWallCollision();
	bool hit(SDL_Rect object);
	void render(SDL_Renderer* renderer);
	SDL_Rect getDest();
	
};

#endif // !PROJECTILE_H
