#include "Widget.h"
#include <string>
#include <SDL.h>

// Standard Constructor for Widget
Widget::Widget(int start_x, int start_y, SDL_Renderer* renderer, SDL_Window* window)
{
	pos.x = start_x;
	pos.y = start_y;
	this->renderer = renderer;
	this->window = window;
}

// Set the X position of the Widget
void Widget::setX(int x)
{
	pos.x = x;
}

// Set the Y position of the Widget
void Widget::setY(int y)
{
	pos.y = y;
}

// Set the X position of the Widget
int Widget::getX()
{
	return pos.x;
}

// Set the Y position of the Widget
int Widget::getY()
{
	return pos.y;
}


// Destructor for Widget
Widget::~Widget()
{
}
