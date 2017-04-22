#include "Widget.h"
#include <string>
#include <SDL2/SDL.h>

// Standard Constructor for Widget
Widget::Widget(int start_x, int start_y, SDL_Renderer* renderer, SDL_Window* window)
{
	pos.x = start_x;
	pos.y = start_y;
	this->renderer = renderer;
	this->window = window;
	this->locked = true;
}

// Set the X position of the Widget
void Widget::setX(int x)
{
	if (!locked){
		pos.x = x;
	}
}

// Set the Y position of the Widget
void Widget::setY(int y)
{
	if (!locked){
		pos.y = y;
	}
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

// If x and y are within boundaries of widget, toggle widget lock
void Widget::toggleLock(int x, int y)
{
	if (x > pos.x && y > pos.y && x < pos.x + pos.w && y < pos.y + pos.h){
		locked = !locked;
	}
	return;
}

// Destructor for Widget
Widget::~Widget()
{
}
