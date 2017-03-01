#include "Basic_Image.h"
#include <string>
#include <SDL.h>
#include <iostream>

// Standard Constructor
Basic_Image::Basic_Image(int start_x, int start_y, SDL_Renderer *renderer, SDL_Window *window, std::string file_source) : Widget(start_x, start_y, renderer, window)
{
	image_location = file_source;

	// Load the image to use
	SDL_Surface *image_surface = SDL_LoadBMP(image_location.c_str());

	//Make sure the load went well
	if (image_surface == nullptr){
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
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

}

// Draws the image widget
void Basic_Image::draw()
{
	// Draw test bmp texture
	for (int i = 0; i < 5; ++i){
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		// Wait 1 seconds
		SDL_Delay(1000);
	}
}

// Destructor
Basic_Image::~Basic_Image()
{
	SDL_DestroyTexture(texture);
}
