#include "Projectile.h"

Projectile::Projectile(SDL_Renderer* renderer, int x, int y, int XVelocity, int YVelocity, int spriteWidth, int SpriteHeight)
{	
	Projectile::x = x;
	Projectile::y = y;
	Projectile::XVelocity = XVelocity;
	Projectile::YVelocity = YVelocity;
	texture = new Texture("projectile.png", renderer, SDL_Rect{ 0, 0, 4, 4 }, SDL_Rect{ x, y, spriteWidth, SpriteHeight });
}

Projectile::~Projectile()
{
	delete texture;
}

void Projectile::accelerate()
{
	x += XVelocity;
	y += YVelocity;
	texture->setCoords(x, y);
}

bool Projectile::detectWallCollision()
{
	if (x >= 640 || x <= 0 || y <= 0 || y >= 480)
	{
		return true;
	}
	else return false;
}

bool Projectile::hit(SDL_Rect object)
{
	if (SDL_HasIntersection(&texture->getDest(), &object)) return true;
	else return false;
}

void Projectile::render(SDL_Renderer* renderer)
{
	texture->render(renderer);
}

SDL_Rect Projectile::getDest()
{
	return texture->getDest();
}