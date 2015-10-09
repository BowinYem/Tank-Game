#include "Turret.h"

Turret::Turret(Texture* texture, int rotateSpeed, SDL_Renderer* renderer)
{
	Turret::texture = texture;
	Turret::rotateSpeed = rotateSpeed;
	turretAngle = 0;
	projectiles = vector<Projectile*>(5);
	setTrajectory();
	laser = new Laser(texture->getXCoord(), texture->getYCoord(), xTrajectory, yTrajectory, 20, 100, turretAngle-90, renderer);
	laser->updateLaser(texture->getXCoord(), texture->getYCoord(), xTrajectory, yTrajectory, turretAngle - 90);
	laserOn = false;
}

void Turret::rotateLeft()
{
	turretAngle -= rotateSpeed;
	texture->setAngle(turretAngle);
	setTrajectory();

	laser->updateLaser(texture->getXCoord(), texture->getYCoord(), xTrajectory, yTrajectory, turretAngle-90);
}

void Turret::rotateRight()
{
	turretAngle += rotateSpeed;
	texture->setAngle(turretAngle);
	setTrajectory();

	laser->updateLaser(texture->getXCoord(), texture->getYCoord(), xTrajectory, yTrajectory, turretAngle-90);
}

void Turret::setPosition(int x, int y)
{
	texture->setCoords(x, y);
	setTrajectory();

	laser->updateLaser(texture->getXCoord(), texture->getYCoord(), xTrajectory, yTrajectory, turretAngle-90);
}

void Turret::shoot(SDL_Renderer* renderer)
{
	if (curProjectiles < maxProjectiles)
	{
		//projectiles = new Projectile(renderer, texture->getXCoord(), texture->getYCoord(), xTrajectory, yTrajectory);
		//projectiles.push_back(Projectile(renderer, texture->getXCoord(), texture->getYCoord(), xTrajectory, yTrajectory));

		setTrajectory();
		for (int i = 0; i < projectiles.size(); i++)
		{
			if (projectiles[i] == NULL)
			{
				projectiles[i] = new Projectile(renderer, texture->getXCoord(), texture->getYCoord(), xTrajectory, yTrajectory, 4, 4);
				curProjectiles++;
				break; 
			}
		}
	}
}

void Turret::extendLaser(SDL_Renderer* renderer)
{
	laserOn = true;
	laser->extend(renderer);
}

void Turret::retractLaser()
{
	laserOn = false;
	laser->retract();
}

bool Turret::projectilesExist()
{
	return projectilesOnScreen;
}

bool Turret::detectProjectileHit(SDL_Rect object)
{
	//Iterate though all of the projectiles and see if any of them intersects with object
	//If projectile has made contact, destroy the projectile
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i] != NULL)
		{
			if (SDL_HasIntersection(&object, &projectiles[i]->getDest()))
			{
				projectiles[i]->destroyProjectile();
				delete projectiles[i];
				projectiles[i] = NULL;
				curProjectiles--; 
				return true;
			}
		}
	}

	return false;
}

void Turret::updateProjectiles()
{
	//Iterate through the projectiles container and accelerate each time
	for (int x = 0; x < projectiles.size(); x++)
	{
		if (projectiles[x] != NULL)
		{
			if (projectiles[x]->detectWallCollision())
			{
				projectiles[x]->destroyProjectile();
				delete projectiles[x];
				projectiles[x] = NULL;
				curProjectiles--;
			}
			else projectiles[x]->accelerate();
		}
	}
}

void Turret::setTrajectory()
{
	/*
	This function sets the tracjectory for projectiles and lasers.
	*/

	double pi = 3.1415926535897;
	int radius = texture->getSourceWidth()/2;
	int turretPosX = texture->getXCoord();
	int turretPosY = texture->getYCoord();
	double currAngle;
	int facingX;
	int facingY;

	//Find the degree of the angle here with this if else
	if (turretAngle < 0)
	{
		currAngle = 360 + (turretAngle % 360);
	}
	else currAngle = turretAngle % 360;

	//Given the x and y positions of the turret itself and the current angle of the turret, we get the coordinates for a corresponding point on the edge 
	//of the "rotation circle" with these math formulas. 
	facingX = texture->getXCoord() + radius * cos(currAngle * (pi / 180));
	facingY = texture->getYCoord() + radius * sin(currAngle * (pi / 180));

	//Find our trajactory via the slope formula 
	xTrajectory = (facingX - turretPosX);
	yTrajectory = (facingY - turretPosY);	
}

void Turret::renderProjectiles(SDL_Renderer* renderer)
{
	//Iterate through the projectiles container and render each time
	for (int x = 0; x < projectiles.size(); x++)
	{
		if (projectiles[x] != NULL) projectiles[x]->render(renderer);
	}
}

void Turret::render(SDL_Renderer* renderer)
{
	texture->render(renderer);
	renderProjectiles(renderer);
	if (laserOn)
	{
		laser->render(renderer);
	}
}

void Turret::destroyTurret()
{
	delete texture;
}