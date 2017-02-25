#include <iostream>
#include <string>
#include <SDL.h>


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

	// Load the bmp
	std::string imagePath = "test_img.bmp";
	SDL_Surface *test_image = SDL_LoadBMP(imagePath.c_str());
	if (test_image == nullptr){
		SDL_DestroyRenderer(main_renderer);
		SDL_DestroyWindow(main_window);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Create texture from test image bmp
	SDL_Texture *test_texture = SDL_CreateTextureFromSurface(main_renderer, test_image);
	SDL_FreeSurface(test_image);
	if (test_texture == nullptr){
		SDL_DestroyRenderer(main_renderer);
		SDL_DestroyWindow(main_window);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Draw test bmp texture
	for (int i = 0; i < 3; ++i){
		SDL_RenderClear(main_renderer);
		SDL_RenderCopy(main_renderer, test_texture, NULL, NULL);
		SDL_RenderPresent(main_renderer);
		// Wait 6 seconds
		SDL_Delay(2000);
	}

	SDL_DestroyTexture(test_texture);
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
	SDL_Quit();
	return 0;
}