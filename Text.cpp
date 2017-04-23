#include "Text.h"
#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_ttf.h>

//Text constructor
Text::Text(int start_x, int start_y, SDL_Renderer *renderer, SDL_Window *window, std::string font_name, SDL_Color color, std::string text_val, int pt_size) : Widget(start_x, start_y, renderer, window)
{
	this->text = text_val;
	this->color = color;
	this->size = pt_size;

	// Create and store the font
	font = TTF_OpenFont(font_name.c_str(), size);
	// Make sure the font load was successful
    
	if (font == nullptr){
		std::cout << "TTF_OpenFont Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Create and render the text surface
	SDL_Surface* text_surface = TTF_RenderText_Solid(font,text_val.c_str(),color);
	// Make sure the text load was successful
	if (text_surface == nullptr){
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		std::cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	// Create texture from loaded image
	texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	// We don't need the surface after texture creation
	SDL_FreeSurface(text_surface);

	// Make sure the texture was created successfully
	if (texture == nullptr){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}
	//Set information about texture
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
}
// Draws the image widget
void Text::draw()
{


	if (!hidden){
		// Draw test text texture
		SDL_RenderCopy(renderer, texture, NULL, &pos);
		if (!locked){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(renderer, &pos);
		}
	}
}
// Changes the text string to be displayed
void Text::changeText(std::string new_text)
{
	// Create and render the text surface
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, new_text.c_str(), color);
	// Make sure the text load was successful
	if (text_surface == nullptr){
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		std::cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	// Create texture from loaded image
	texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	// We don't need the surface after texture creation
	SDL_FreeSurface(text_surface);

	// Make sure the texture was created successfully
	if (texture == nullptr){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	//Set information about texture
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
}
// Changes the font to be displayed
void Text::changeFont(std::string new_font, int new_size)
{
	this->size = new_size;
	// Create and store the font
	font = TTF_OpenFont(new_font.c_str(), size);
	// Make sure the font load was successful
	if (font == nullptr){
		std::cout << "TTF_OpenFont Error: " << SDL_GetError() << std::endl;
		return;
	}
	// Create and render the text surface
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	// Make sure the text load was successful
	if (text_surface == nullptr){
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		std::cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	// Create texture from loaded image
	texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	// We don't need the surface after texture creation
	SDL_FreeSurface(text_surface);

	// Make sure the texture was created successfully
	if (texture == nullptr){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	//Set information about texture
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
}
//Text destructor
Text::~Text()
{
}
