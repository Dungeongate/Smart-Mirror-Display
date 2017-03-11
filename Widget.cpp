#include "Widget.h"
#include <string>
#include <iostream>
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


//figure out how to make this work with mouse movements

// handles all the input events on the widget
void Widget::handle_events(SDL_Event e)
{

	int mouse_x, mouse_y;
	switch(e.type){
	case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON(SDL_BUTTON_LEFT)){
			SDL_GetMouseState(&mouse_x, &mouse_y);
			// within the bounds of the image
			if (mouse_over_widget(mouse_x, mouse_y)){
				std::cout << "Hit";
			}
			else{
				std::cout << "Miss";
			}

		}
	}
}

// returns true if mouse is over widget
bool Widget::mouse_over_widget(int mouse_x, int mouse_y){
	return mouse_x >= pos.x && mouse_x <= pos.x + pos.w && mouse_y >= pos.y && mouse_y <= pos.y + pos.h;
}



// Destructor for Widget
Widget::~Widget()
{
}
