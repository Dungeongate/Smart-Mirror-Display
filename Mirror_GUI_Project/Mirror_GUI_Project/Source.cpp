#include <iostream>
#include <string>
#include <SDL.h>
#include "Widget.h"
#include "Basic_Image.h"


int main(int, char**){
	// Initialize video only for now
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Create main window
	SDL_Window *main_window = SDL_CreateWindow("GUI window test text", 100, 100, 1600, 900, SDL_WINDOW_SHOWN);
	if (main_window == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Create renderer to draw to main window
	// Second parameter indicates index of redering driver to be used, -1 selects the first usable driver
	SDL_Renderer *main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (main_renderer == nullptr){
		SDL_DestroyWindow(main_window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	Basic_Image happyface(0,0,main_renderer,main_window,"happyface.bmp");
	happyface.draw();

	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
	SDL_Quit();
	return 0;
}