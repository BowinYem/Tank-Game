#ifndef TANK_H
#define TANK_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Turret.h"
#include "Texture.h"


class Tank{

protected:
	
	Texture* texture;
	Turret* tankTurret;
	SDL_Rect hitbox;


	int accelerateSpeed;
	int rotateSpeed;
	int tankAngle = 0;
	int facingX;
	int facingY;
	int turretPosX;
	int turretPosY;

	void updateTurretPosition();
	void updateHitbox();

public:

	Tank(Texture* texture, int accelerateSpeed, int rotateSpeed, int turretRotateSpeed, SDL_Renderer* renderer);
	void accelerate(int direction, float elaspedTime);
	void shoot(SDL_Renderer* renderer);
	void extendLaser();
	void retractLaser();
	void updateProjectiles();
	bool projectilesExist();
	bool detectProjectileHit(SDL_Rect object);
	void rotateLeft();
	void rotateRight();
	void rotateTurretLeft();
	void rotateTurretRight();
	void setFacing();
	void render(SDL_Renderer* renderer);
	void setSource(SDL_Rect source);
	void setDest(SDL_Rect dest);
	bool detectColision(SDL_Rect object);
	SDL_Rect getSource();
	SDL_Rect getDest();
	SDL_Rect getHitbox();
	void destroyTank();



};


#endif 
