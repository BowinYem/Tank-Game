#ifndef TURRET_H
#define TURRET_H
#include <SDL.h>
#include <vector>
#include "Texture.h"
#include "Projectile.h"
#include "Laser.h"
using namespace std;

class Turret
{
protected:

	int turretAngle;
	int rotateSpeed;
	int xTrajectory;
	int yTrajectory;
	int curProjectiles = 0;
	int maxProjectiles = 3;
	bool projectilesOnScreen;
	bool laserOn;
	Texture* texture;
	vector<Projectile*> projectiles;
	vector<Projectile*>::iterator iterator;
	Laser* laser;
	void setTrajectory();
	void renderProjectiles(SDL_Renderer* renderer);

public:

	Turret(Texture* texture, int rotateSpeed, SDL_Renderer* renderer);
	void rotateLeft();
	void rotateRight();
	void setPosition(int x, int y);
	void shoot(SDL_Renderer* renderer);
	void extendLaser();
	void detractLaser();
	bool projectilesExist();
	bool detectProjectileHit(SDL_Rect object);
	void updateProjectiles();
	void render(SDL_Renderer* renderer);
	void destroyTurret();
};


#endif // !TURRET_H
