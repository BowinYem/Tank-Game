#include "Laser.h"

Laser::Laser(int x, int y, int run, int rise, int bitWidth, int bitLength, int totalLength, SDL_Renderer* renderer) : x(x), y(y), hitX(x), hitY(y),
run(run), rise(rise), bitWidth(bitWidth), bitLength(bitLength), totalLength(totalLength), renderer(renderer)
{
	laserTextures = vector<Texture*>(totalLength);
	//laserTextures[0] = new Texture("hitbox.png", renderer, SDL_Rect{ 0, 0, SPRITE_WIDTH, SPRITE_LENGTH }, SDL_Rect{ Laser::x + run , Laser::y + rise, bitWidth, bitLength });
	//hitboxes[0] = SDL_Rect{ Laser::x + run, Laser::y + rise, bitWidth, bitLength };
	extended = false;
}

void Laser::extend()
{
	extended = true;
}

void Laser::retract()
{
	extended = false;
}

bool Laser::hit(SDL_Rect object)
{
	for (int i = 0; i < laserTextures.size(); i++)
	{
		if (SDL_HasIntersection(&laserTextures[i]->getDest(), &object)) return true;
	}
	return false; 
}

void Laser::updateLaser(int x, int y, int run, int rise)
{
	Laser::run = run;
	Laser::rise = rise;

	hitX = x + (run * 2);
	hitY = y + (rise * 2);

	for (int i = 0; i < laserTextures.size(); i++)
	{
		delete laserTextures[i];
		laserTextures[i] = new Texture("hitbox.png", renderer, SDL_Rect{ 0, 0, SPRITE_WIDTH, SPRITE_LENGTH}, SDL_Rect{ hitX, hitY, bitWidth, bitLength });

		hitX += (run);
		hitY += (rise);
	}
}

bool Laser::isExtended()
{
	return extended;
}

void Laser::render()
{
	for (int i = 0; i < laserTextures.size(); i++)
	{
		laserTextures[i]->render(renderer);
	}
	
}

void Laser::increaseBitWidth(int x)
{
	bitWidth += x;
}

void Laser::increaseBitLength(int x)
{
	bitLength += x;
}