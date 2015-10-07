#include "Texture.h"

Texture::Texture(){}

Texture::Texture(char* path, SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		cout << "IMG_LOAD FAILED";
	}

	if (SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF)) == -1)
	{
		cout << "SDL_SETCOLORKEY FAILED";
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

Texture::Texture(char* path, SDL_Renderer* renderer, SDL_Rect source, SDL_Rect dest)
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	Texture::source = source;
	Texture::dest = dest;
	SDL_FreeSurface(surface);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

void Texture::render(SDL_Renderer* renderer)
{
	if (SDL_RenderCopyEx(renderer, texture, &source, &dest, angle, NULL, SDL_FLIP_NONE) == -1)
	{
		cout << "SDL_RENDERCOPYEX FAILED" << endl;
	}
}

void Texture::setSource(SDL_Rect source)
{
	Texture::source = source;
}

void Texture::setDest(SDL_Rect dest)
{
	Texture::dest = dest;
}

void Texture::setAngle(double angle)
{
	Texture::angle = angle;
}

void Texture::setCoords(int x, int y)
{
	dest.x = x;
	dest.y = y;
}

int Texture::getXCoord()
{
	return dest.x;
}

int Texture::getYCoord()
{
	return dest.y;
}

SDL_Rect Texture::getSource()
{
	return source;
}

SDL_Rect Texture::getDest()
{
	return dest;
}

double Texture::getAngle()
{
	return angle;
}

int Texture::getSourceWidth()
{
	return source.w;
}

int Texture::getSourceHeight()
{
	return source.h;
}




