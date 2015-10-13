#include "Laser.h"

Laser::Laser(int x, int y, int run, int rise, int width, int maxLength, double angle, SDL_Renderer* renderer) : x(x), y(y), hitX(x), hitY(y),
run(run), rise(rise), width(width), maxLength(maxLength), renderer(renderer)
{
	hitboxes = vector<Texture*>(10);
	texture = new Texture("projectile.png", renderer, SDL_Rect{ 0, 0, 20, 20 }, SDL_Rect{ x, y, width, maxLength });
	texture->setAngle(angle);


	hitboxes[0] = new Texture("hitbox.png", renderer, SDL_Rect{ 0, 0, 20, 20 }, SDL_Rect{ Laser::x + run, Laser::y + rise, 20, 20 });
	extended = false;
}

void Laser::extend()
{
	//This function will expand the laser towards the tracjectory (based on x velocity and y velocity)
	//1. place a SDL_Rect at x and y. These are the hitboxes.
	//2. increment x and y by XVelocity and YVelocity, respectively.
	//Do this until the laser hits the max length of the laser

	extended = true;
}

void Laser::retract()
{
	extended = false;
}

bool Laser::hit(SDL_Rect object)
{
	return true; //placeholder
}

void Laser::updateLaser(int x, int y, int run, int rise, double angle)
{
	//For updating the laser, maybe just empty the hixboxes vector, reset the iterator, and call expand again?

	//Also change the angle and position of the laser texture and the run/rise.
	texture->setCoords(x, y);
	Laser::run = run;
	Laser::rise = rise;
	texture->setAngle(angle);
	texture->setRotationPoint(new SDL_Point{ 10, 10 });

	hitX = x;
	hitY = y;

	for (int i = 0; i < hitboxes.size(); i++)
	{
		delete hitboxes[i];
		hitboxes[i] = new Texture("hitbox.png", renderer, SDL_Rect{ 0, 0, 20, 20 }, SDL_Rect{ hitX, hitY, 20, 20 });
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

	texture->render(renderer);
	

	
	for (int i = 0; i < hitboxes.size(); i++)
	{
		hitboxes[i]->render(renderer);
	}
	

	//hitboxes[0]->render(renderer);


}

