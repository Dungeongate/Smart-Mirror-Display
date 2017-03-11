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
	SDL_Window *main_window = SDL_CreateWindow("GUI window test text", 0, 0, 1920, 1080, SDL_WINDOW_SHOWN);
	if (main_window == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 2;
	}

	// Create renderer to draw to main window
	// Second parameter indicates index of redering driver to be used, -1 selects the first usable driver
	SDL_Renderer *main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (main_renderer == nullptr){
		SDL_DestroyWindow(main_window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 3;
	}

	//Create keyboard state
	const Uint8 *key_state = SDL_GetKeyboardState(NULL);

	SDL_Event E;

	Basic_Image text_test(0, 0, main_renderer, main_window, "text.bmp");
	Basic_Image clock_image(200, 100, main_renderer, main_window, "clock_test.bmp");

	// Main Loop
	while (!key_state[SDL_SCANCODE_ESCAPE]){
		// Update event states
		SDL_PumpEvents();
		SDL_PollEvent(&E);
		text_test.draw();
		clock_image.draw();


		if (key_state[SDL_SCANCODE_RIGHT])
			clock_image.setX(clock_image.getX() + 15);
		if (key_state[SDL_SCANCODE_LEFT])
			clock_image.setX(clock_image.getX() - 15);
		if (key_state[SDL_SCANCODE_UP])
			clock_image.setY(clock_image.getY() - 15);
		if (key_state[SDL_SCANCODE_DOWN])
			clock_image.setY(clock_image.getY() + 15);


		clock_image.handle_events(E);
	}
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
	SDL_Quit();
	return 0;
}