#include "Laser.h"

void Laser::extend(SDL_Renderer* renderer)
{
	//This function will expand the laser towards the tracjectory (based on x velocity and y velocity)
	//1. place a SDL_Rect at x and y. These are the hitboxes.
	//2. increment x and y by XVelocity and YVelocity, respectively.
	//Do this until the laser hits the max length of the laser

	for (int i = 0; i < hitboxes.size(); i++)
	{
		hitboxes[i] = new Texture("hitbox.png", renderer, SDL_Rect{ 0, 0, 20, 20 }, SDL_Rect{ hitX, hitY, 20, 20 });

		hitX += run;
		hitY += rise;
		
	}

}

void Laser::retract()
{

	for (int i = 0; i < hitboxes.size(); i++)
	{
		delete hitboxes[i];
		hitboxes[i] = NULL;

		hitX = x;
		hitY = y;

	}
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
}

void Laser::render(SDL_Renderer* renderer)
{

	//texture->render(renderer);

	for (int i = 0; i < hitboxes.size(); i++)
	{
		hitboxes[i]->render(renderer);
	}


}

