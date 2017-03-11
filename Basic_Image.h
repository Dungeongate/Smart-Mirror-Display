#pragma once
#include "Widget.h"
#include <SDL.h>
#include <string>

class Basic_Image: public Widget
{
public:
	Basic_Image(int, int, SDL_Renderer*, SDL_Window*, std::string);
	void draw();
	~Basic_Image();
private:
	std::string image_location;
	SDL_Texture* texture;
};

