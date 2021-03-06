#pragma once
#include <SDL.h>
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

	void toggleLock();
	void toggleHidden();
	bool insideBound(int, int);
	bool hidden;
    bool locked;
protected:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Rect pos;
};

