#include <iostream>
#include <string>
#include "sqlite3.h"
#include "TextDatabase.h"
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL2/SDL.h>
#include "Widget.h"
#include "Basic_Image.h"
//Xcode version of #include <SDL.h> is #include <SDL2/SDL.h>



int main(int, char**) {
    // Text Database Code //
    char *input="test.db";
    textdatabase databaseinfo(input);
    databaseinfo.getQuote();
    
    // Initialize video only for now
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // Create main window
    SDL_Window *main_window = SDL_CreateWindow("GUI window test text", 100, 100, 2500, 1300, SDL_WINDOW_SHOWN || SDL_WINDOW_RESIZABLE);
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
    
    Basic_Image clock_image(200, 100, main_renderer, main_window, "clock_test.png");
	Basic_Image test_image(0, 0, main_renderer, main_window, "test.png");
	Basic_Image test_image2(0, 100, main_renderer, main_window, "test.png");

	clock_image.draw();
	test_image.draw();

	bool end_main_loop = false;
    // Main Loop
	while (!end_main_loop){
		// Event handling
		while (SDL_PollEvent(&E) != 0){
			switch (E.type){
			case SDL_KEYDOWN:
				switch (E.key.keysym.sym){
				case SDLK_ESCAPE:
					end_main_loop = true;
					break;
				case SDLK_LEFT:
					clock_image.setX(clock_image.getX() - 15);
					break;
				case SDLK_RIGHT:
					clock_image.setX(clock_image.getX() + 15);
					break;
				case SDLK_UP:
					clock_image.setY(clock_image.getY() - 15);
					break;
				case SDLK_DOWN:
					clock_image.setY(clock_image.getY() + 15);
					break;
				}
				break;
			case SDL_QUIT:
				end_main_loop = true;
				break;
			}
		}
		SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0);
		SDL_RenderClear(main_renderer);

		test_image.draw();
		test_image2.draw();
		clock_image.draw();

		//update screen
		SDL_RenderPresent(main_renderer);
	}
    return 0;
}
