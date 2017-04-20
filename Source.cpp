#include <iostream>
#include <string>
#include "sqlite3.h"
#include "TextDatabase.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <SDL2/SDL.h>
#include "Widget.h"
#include "Basic_Image.h"
#include "Text.h"
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
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf Error:" << TTF_GetError() << std::endl;
		return 4;
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

	SDL_Color text_color = { 255, 255, 255 };
	Text test_text(200, 500, main_renderer, main_window, "RAPSCALL.ttf", text_color,"hello world!", 50);

	int count = 0;

	bool end_main_loop = false;
    // Main Loop
	while (!end_main_loop){
		// Event handling
		while (SDL_PollEvent(&E) != 0){
			switch (E.type){
			// User presses a key
			case SDL_KEYDOWN:
				switch (E.key.keysym.sym){
				// Escape key pressed
				case SDLK_ESCAPE:
					end_main_loop = true;
					break;
				// Left key pressed
				case SDLK_LEFT:
					test_image.setX(test_image.getX() - 15);
					test_image2.setX(test_image2.getX() - 15);
					clock_image.setX(clock_image.getX() - 15);
					test_text.setX(test_text.getX() - 15);
					break;
				// Right key pressed
				case SDLK_RIGHT:
					test_image.setX(test_image.getX() + 15);
					test_image2.setX(test_image2.getX() + 15);
					clock_image.setX(clock_image.getX() + 15);
					test_text.setX(test_text.getX() + 15);
					break;
				// Up key pressed
				case SDLK_UP:
					test_image.setY(test_image.getY() - 15);
					test_image2.setY(test_image2.getY() - 15);
					clock_image.setY(clock_image.getY() - 15);
					test_text.setY(test_text.getY() - 15);
					break;
				// Down key pressed
				case SDLK_DOWN:
					test_image.setY(test_image.getY() + 15);
					test_image2.setY(test_image2.getY() + 15);
					clock_image.setY(clock_image.getY() + 15);
					test_text.setY(test_text.getY() + 15);
					break;
				case SDLK_CAPSLOCK:
					count++;
					test_text.changeText(std::to_string(count));
					break;
				case SDLK_SPACE:
					test_image.changeImage("clock_test.png");
					break;
				}
				break;
			// Mouse button pressed
			case SDL_MOUSEBUTTONDOWN:
				switch (E.button.button){
				// Left mouse pressed
				case SDL_BUTTON_LEFT:
					test_image.toggleLock(E.motion.x, E.motion.y);
					test_image2.toggleLock(E.motion.x, E.motion.y);
					clock_image.toggleLock(E.motion.x,E.motion.y);
					test_text.toggleLock(E.motion.x, E.motion.y);
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
		test_text.draw();

		//update screen
		SDL_RenderPresent(main_renderer);
	}

    return 0;
}
