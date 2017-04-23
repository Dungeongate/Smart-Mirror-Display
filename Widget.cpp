#include "Widget.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

// Standard Constructor for Widget
Widget::Widget(int start_x, int start_y, SDL_Renderer* renderer, SDL_Window* window)
{
	pos.x = start_x;
	pos.y = start_y;
	this->renderer = renderer;
	this->window = window;
	this->locked = true;

	this->hidden = false;
}

// Set the X position of the Widget
void Widget::setX(int x)
{

	if (!locked && !hidden){
		pos.x = x;
	}
}

// Set the Y position of the Widget
void Widget::setY(int y)
{

	if (!locked && !hidden){

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
void Widget::toggleLock()
{
	locked = !locked;
	return;
}

// If x and y are within boundaries of widget, toggle widget hidden
void Widget::toggleHidden()
{
	hidden = !hidden;
	return;
}

// Returns true only if x and y are within the rectangle bound of the widget
bool Widget::insideBound(int x, int y)
{
	if (x > pos.x && y > pos.y && x < pos.x + pos.w && y < pos.y + pos.h){
		return true;
	}
	return false;
}

// Destructor for Widget
Widget::~Widget()
{
}
