#include "Basic_Image.h"
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

// Standard Constructor
Basic_Image::Basic_Image(int start_x, int start_y, SDL_Renderer *renderer, SDL_Window *window, std::string file_source) : Widget(start_x, start_y, renderer, window)
{
	image_location = file_source;

	// Load the image to use
	SDL_Surface *image_surface = IMG_Load(image_location.c_str());

	//Make sure the load succeeded
	if (image_surface == nullptr){
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	// Create texture from loaded image
	texture = SDL_CreateTextureFromSurface(renderer, image_surface);

	// We don't need the surface after texture creation
	SDL_FreeSurface(image_surface);

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
void Basic_Image::draw()
{
	// Draw test bmp texture
	SDL_RenderCopy(renderer, texture, NULL, &pos);
}

// Changes the image to be drawn
void Basic_Image::changeImage(std::string new_image_location)
{
	image_location = new_image_location;

	// Load the image to use
	SDL_Surface *image_surface = IMG_Load(image_location.c_str());

	//Make sure the load succeeded
	if (image_surface == nullptr){
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	// Create texture from loaded image
	texture = SDL_CreateTextureFromSurface(renderer, image_surface);

	// We don't need the surface after texture creation
	SDL_FreeSurface(image_surface);

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

// Destructor
Basic_Image::~Basic_Image()
{
	SDL_DestroyTexture(texture);
}
