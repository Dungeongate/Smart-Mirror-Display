#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
// Widgets are any drawable object that has an alterable position
class Widget
{
public:
	Widget(int, int, SDL_Renderer*, SDL_Window*);
	~Widget();
	void setX(int);
	void setY(int);
	int getX();
	int getY();
	void toggleLock(int,int);
protected:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Rect pos;
	bool locked;
};

