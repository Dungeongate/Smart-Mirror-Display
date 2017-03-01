#include "Widget.h"
#include <string>
#include <SDL.h>

// Standard Constructor for Widget
Widget::Widget(int start_x, int start_y, SDL_Renderer* renderer, SDL_Window* window)
{
	this->x = start_x;
	this->y = start_y;
	this->renderer = renderer;
	this->window = window;
}

// Set the X position of the Widget
void Widget::setX(int x)
{
	this->x = x;
}

// Set the Y position of the Widget
void Widget::setY(int y)
{
	this->y = y;
}

// Set the X position of the Widget
int Widget::getX()
{
	return x;
}

// Set the Y position of the Widget
int Widget::getY()
{
	return y;
}


// Destructor for Widget
Widget::~Widget()
{
}
