#pragma once
#include "Widget.h"
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

class Text: public Widget
{
public:
	Text(int, int, SDL_Renderer*, SDL_Window*, std::string, SDL_Color, std::string, int);
	void draw();
	~Text();
private:
	std::string text;
	SDL_Texture* texture;
	SDL_Color color;
	TTF_Font *font;
};
