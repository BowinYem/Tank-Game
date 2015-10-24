#include "Texture.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "Tank.h"
#include "Meteor.h"
#include "Music.h"

class Game{

	//CONSTANTS
	const int WINDOW_HEIGHT = 480;
	const int WINDOW_WIDTH = 640;
	const int PLAYER_SPRITE_WIDTH = 40;
	const int PLAYER_SPRITE_HEIGHT = 40;
	const int TURRET_SPRITE_WIDTH = 20;
	const int TURRET_SPRITE_HEIGHT = 20;
	const int PLAYER_SPAWN_X = 200;
	const int PLAYER_SPAWN_Y = 200;	
	const int TANK_SPEED = 100; //I'm not sure if we're actually using this anymore.
	const int TANK_ROTATE_SPEED = 2;
	const int TURRET_ROTATE_SPEED = 2;
	const int MAX_METEORS = 10;

	//PLAYER STUFF
	int playerAngle = 0;
	int turretAngle = 0;
	int currPosX = PLAYER_SPAWN_X;
	int currPosY = PLAYER_SPAWN_Y;
	int facingX;
	int facingY;
	Tank* playerTank;
	
	//METEOR STUFF
	vector<Meteor*> meteors;
	int currentMeteors = 0;
	int meteorMaxVelocity = 2;
	int maxMeteorWidth = 100;
	int maxMeteorHeight = 100;

	//TIMERS
	double elapsedTime;
	Uint32 timer;
	double meteorSpawnTimer;
	Uint32 meteorTimer;
	double meteorSpawnTime = 1;

	//GAME STUFF
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	SDL_Event e;
	bool quit = false;

	//MUSIC/SOUND STUFF
	Music* music;
	bool musicPlaying = false;

	void init()
	{

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			cout << "SDL_INIT has Failed";
		}

		gameWindow = SDL_CreateWindow("TANK GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, NULL);

		if (gameWindow == 0)
		{
			cout << "SDL_CreateWindow Failed";
		}

		gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (gameRenderer == NULL)
		{
			cout << "SDL_CreateRenderer Failed";
		}

		if (IMG_Init(IMG_INIT_PNG) == 0)
		{
			cout << "IMG_INIT_PNG has Failed";
		}

		if (SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF) == -1)
		{
			cout << "SDL_SetRenderDrawColor has Failed";
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mix_OpenAudio has Failed";
		}

		
		playerTank = new Tank(new Texture("player.png", gameRenderer, SDL_Rect{0, 0, 20, 20}, SDL_Rect{PLAYER_SPAWN_X, PLAYER_SPAWN_Y, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT}), 
			TANK_SPEED, TANK_ROTATE_SPEED, TURRET_ROTATE_SPEED, gameRenderer); 

		meteors = vector<Meteor*>(MAX_METEORS);

		music = new Music("music.wav");
	}

	void clean()
	{
		SDL_DestroyWindow(gameWindow);
		SDL_DestroyRenderer(gameRenderer);
		gameWindow = NULL;
		gameRenderer = NULL;
		playerTank->destroyTank();

		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void getInput()
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		const Uint8* input = SDL_GetKeyboardState(NULL);
		handleInput(input);
	}

	void handleInput(const Uint8* input)
	{
		if (input[SDL_SCANCODE_ESCAPE])
		{
			quit = true;
		}

		if (input[SDL_SCANCODE_LEFT])
		{
			playerTank->rotateLeft();
		}

		if (input[SDL_SCANCODE_RIGHT])
		{
			playerTank->rotateRight();
		}

		if (input[SDL_SCANCODE_A])
		{
			playerTank->rotateTurretLeft();
		}

		if (input[SDL_SCANCODE_D])
		{
			playerTank->rotateTurretRight();
		}

		if (input[SDL_SCANCODE_UP])
		{
			playerTank->setFacing();
			playerTank->accelerate(0, elapsedTime);

		}

		if (input[SDL_SCANCODE_DOWN])
		{
			playerTank->setFacing();
			playerTank->accelerate(1, elapsedTime);
		}

		if (input[SDL_SCANCODE_SPACE])
		{
			playerTank->shoot(gameRenderer);
		}

		if (input[SDL_SCANCODE_C])
		{
			playerTank->extendLaser(gameRenderer);
		}
		else playerTank->retractLaser();

		if (input[SDL_SCANCODE_P])
		{
			if (!musicPlaying)
			{
				music->play();
				musicPlaying = true;
			}
			else music->unpause();
		}

		if (input[SDL_SCANCODE_O])
		{
			music->pause();
		}
	}

	void spawnMeteor()
	{
		//Randomly generate spawn coordinates for the meteor.
		//PROBLEM: Generating meteors with no x or y velocity
		int xSpawn = rand() % WINDOW_WIDTH;
		int ySpawn = rand() % WINDOW_HEIGHT;
		int xVel = (rand() % ((meteorMaxVelocity * 2) + 1)) + (-meteorMaxVelocity);
		int yVel; 
		int height = (rand() % maxMeteorHeight) + 2;
		int width = (rand() % maxMeteorWidth) + 2;

		if (xVel == 0)
		{
			yVel = ((rand() % ((meteorMaxVelocity * 2) + 1)) + (-meteorMaxVelocity)) + 1;
		}
		else yVel = (rand() % ((meteorMaxVelocity * 2) + 1)) + (-meteorMaxVelocity);

		for (int i = 0; i < meteors.size(); i++)
		{
			if (meteors[i] == NULL)
			{
				meteors[i] = new Meteor(gameRenderer, xSpawn, ySpawn, xVel, yVel, width, height);
				currentMeteors++;
				break;
			}
		}		
	}

	void accelerateMeteors()
	{
		for (int x = 0; x < meteors.size(); x++)
		{
			if (meteors[x] != NULL)
			{
				if (playerTank->detectWeaponHit(meteors[x]->getDest()))
				{
					if (meteors[x]->getHealth() <= 0)
					{
						cout << "Meteor Destroyed" << endl;
						delete meteors[x];
						meteors[x] = NULL;
						currentMeteors--;
					}
					else
					{
						meteors[x]->decreaseHealth(20);
						cout << "Current health is: " << meteors[x]->getHealth() << endl;
					}

				}
				else if (playerTank->detectColision(meteors[x]->getDest()))
				{
					cout << "You were hit" << endl;
					delete meteors[x];
					meteors[x] = NULL;
					currentMeteors--;
				}
				else if (meteors[x]->detectWallCollision())
				{
					delete meteors[x];
					meteors[x] = NULL;
					currentMeteors--;
				}
				else meteors[x]->accelerate();
			}
		}
	}

	void renderMeteors()
	{
		for (int i = 0; i < meteors.size(); i++)
		{
			if (meteors[i] != NULL) meteors[i]->render(gameRenderer);
		}
	}

	void render()
	{
		if (SDL_RenderClear(gameRenderer) == -1)
		{
			cout << "SDL_RenderClear has Failed";
		}

		playerTank->render(gameRenderer);
		renderMeteors();
		SDL_RenderPresent(gameRenderer);
	}

public:

	void play()
	{
		init();
		timer = SDL_GetTicks();
		meteorTimer = SDL_GetTicks();

		while (quit != true)
		{
			elapsedTime = (SDL_GetTicks() - timer) / 1000.f;
			meteorSpawnTimer = (SDL_GetTicks() - meteorTimer) / 1000.f;
			if (meteorSpawnTimer < meteorSpawnTime + .5 && meteorSpawnTimer > meteorSpawnTime)
			{
				meteorTimer = SDL_GetTicks();
				if (currentMeteors <= MAX_METEORS) spawnMeteor();
			}

			getInput();
			timer = SDL_GetTicks();
			

			accelerateMeteors();
			playerTank->updateProjectiles();

			render();
		}

		clean();
	}

};

int main(int arg, char* argv[])
{
	Game myGame;
	myGame.play();
	return 0;
}