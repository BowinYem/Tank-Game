#include "Tank.h"

void Tank::updateTurretPosition()
{
	turretPosX = texture->getXCoord() + (texture->getSourceWidth() / 2);
	turretPosY = texture->getYCoord() + (texture->getSourceHeight() / 2);
	tankTurret->setPosition(turretPosX, turretPosY);
}

void Tank::updateHitbox()
{
	hitbox.x = texture->getXCoord() + (texture->getSourceWidth() / 2);
	hitbox.y = texture->getYCoord() + (texture->getSourceHeight() / 2);
}

Tank::Tank(Texture* texture, int accelerateSpeed, int rotateSpeed, int turretRotateSpeed, SDL_Renderer* renderer)
{
	Tank::texture = texture;
	Tank::accelerateSpeed = accelerateSpeed;
	Tank::rotateSpeed = rotateSpeed;
	turretPosX = Tank::texture->getXCoord() + (Tank::texture->getSourceWidth() / 2);
	turretPosY = Tank::texture->getYCoord() + (Tank::texture->getSourceHeight() / 2);
	tankTurret = new Turret(new Texture("facing.png", renderer, SDL_Rect{ 0, 0, 20, 20 }, SDL_Rect{ turretPosX, turretPosY, 20, 20 }), turretRotateSpeed, renderer);
	hitbox = SDL_Rect{ Tank::texture->getXCoord(), Tank::texture->getYCoord(), 15, 15 };
}

void Tank::accelerate(int direction, float elapsedTime)
{
	float run;
	float rise;
	float posX = texture->getXCoord();
	float posY = texture->getYCoord();
	float xVelocity;
	float yVelocity;

	//if direction is 0, accelerate foward, everything else accelerates backwards
	if (direction == 0)
	{
		run = facingX - posX;
		rise = facingY - posY;
	}
	else
	{
		run = posX - facingX;
		rise = posY - facingY;
	}


	xVelocity = run * elapsedTime;
	yVelocity = rise * elapsedTime;

	texture->setCoords(posX + xVelocity, posY + yVelocity);
	updateHitbox();
	updateTurretPosition();

}

void Tank::shoot(SDL_Renderer* renderer)
{
	tankTurret->shoot(renderer);
}

void Tank::extendLaser()
{
	tankTurret->extendLaser();
}

void Tank::retractLaser()
{
	tankTurret->detractLaser();
}

void Tank::updateProjectiles()
{
	tankTurret->updateProjectiles();
}

bool Tank::projectilesExist()
{
	return tankTurret->projectilesExist();
}

bool Tank::detectProjectileHit(SDL_Rect object)
{
	return tankTurret->detectProjectileHit(object);
}

void Tank::rotateLeft()
{
	tankAngle -= rotateSpeed;
	texture->setAngle(tankAngle);
}

void Tank::rotateRight()
{
	tankAngle += rotateSpeed;
	texture->setAngle(tankAngle);
}

void Tank::rotateTurretLeft()
{
	tankTurret->rotateLeft();
}

void Tank::rotateTurretRight()
{
	tankTurret->rotateRight();
}

void Tank::setFacing()
{
	double currAngle;
	double pi = 3.1415926535897;
	int radius = 200;
	if (tankAngle < 0)
	{
		currAngle = 360 + (tankAngle % 360);
	}
	else currAngle = tankAngle % 360;

	facingX = texture->getXCoord() + radius * cos(currAngle * (pi / 180));
	facingY = texture->getYCoord() + radius * sin(currAngle * (pi / 180));

}

void Tank::render(SDL_Renderer* renderer)
{
	texture->render(renderer);
	tankTurret->render(renderer);
}

void Tank::setSource(SDL_Rect source)
{
	texture->setSource(source);
}

void Tank::setDest(SDL_Rect dest)
{
	texture->setDest(dest);
}

bool Tank::detectColision(SDL_Rect object)
{
	return SDL_HasIntersection(&hitbox, &object);
}

SDL_Rect Tank::getSource()
{
	return texture->getSource();
}

SDL_Rect Tank::getDest()
{
	return texture->getDest();
}

SDL_Rect Tank::getHitbox()
{
	return hitbox;
}

void Tank::destroyTank()
{
	delete texture;
	tankTurret->destroyTurret();
}