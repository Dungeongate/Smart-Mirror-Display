#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "sqlite3.h"
#include "Clock.h"
#include "Weather\Weather.h"
#include "Widget.h"
#include "Basic_Image.h"
#include "Text.h"
#include "TextDatabase.h"

int main(int, char**) {
    // Text Database Code //
    std::string QueryResult;
    char *input="TextDataBase.db";
    textdatabase databaseinfo(input);


    databaseinfo.CountRows();
    QueryResult=databaseinfo.Query();

	//Initial clock code
	Clock c;
	std::string TIME;

    //Initialize Weather
    //Weather w;

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
    int seconds_per_quote = 5;
    int seconds_since_last_quote = 0;
    std::string last_second = c.getTime();

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
	SDL_Color text_color = { 255, 255, 255 };
	Text CLOCK(200, 100, main_renderer, main_window, "Comfortaa_Regular.ttf", text_color, c.getTime() , 150);
    Text StringQuote(200, 200, main_renderer, main_window, "Comfortaa_Regular.ttf", text_color,QueryResult, 100);
	Text Date(200, 400, main_renderer, main_window, "Comfortaa_Regular.ttf", text_color, c.getDate(), 150);

	bool end_main_loop = false;
    // Main Loop
	while (!end_main_loop){
		SDL_Delay(10);
		c.updateClock();
		CLOCK.changeText(c.getTime());
		Date.changeText(c.getDate());
        if (c.getTime() != last_second){
            last_second = c.getTime();
            seconds_since_last_quote++;
        }
        if (seconds_since_last_quote >= seconds_per_quote){
            // Get the new random quote into QueryResult
            StringQuote.changeText(databaseinfo.Query());
            seconds_since_last_quote = 0;
        }
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
					CLOCK.setX(CLOCK.getX() - 15);
					StringQuote.setX(StringQuote.getX() - 15);
                    Date.setX(Date.getX() - 15);
					break;
				// Right key pressed
				case SDLK_RIGHT:
					CLOCK.setX(CLOCK.getX() + 15);
					StringQuote.setX(StringQuote.getX() + 15);
					Date.setX(Date.getX() + 15);
					break;
				// Up key pressed
				case SDLK_UP:
					CLOCK.setY(CLOCK.getY() - 15);
					StringQuote.setY(StringQuote.getY() - 15);
					Date.setY(Date.getY() - 15);
					break;
				// Down key pressed
				case SDLK_DOWN:
					CLOCK.setY(CLOCK.getY() + 15);
					StringQuote.setY(StringQuote.getY() + 15);
                    Date.setY(Date.getY() + 15);
					break;
				case SDLK_d:
					if (!Date.locked) {
						c.changeDate();
						Date.changeText(c.getDate());
						break;
					}
				// show all hidden widgets
				case SDLK_SPACE:
                    StringQuote.hidden = false;
                    CLOCK.hidden = false;
                    Date.hidden = false;
					break;
				}
				break;
			// Mouse button pressed
			case SDL_MOUSEBUTTONDOWN:
				switch (E.button.button){
				// Left mouse pressed
				case SDL_BUTTON_LEFT:

					//toggle lock of a widget if the mouse is within the bound of the widget
					if (CLOCK.insideBound(E.motion.x, E.motion.y))
						CLOCK.toggleLock();
					if (StringQuote.insideBound(E.motion.x, E.motion.y))
						StringQuote.toggleLock();
                    if (Date.insideBound(E.motion.x, E.motion.y))
                        Date.toggleLock();
					break;
				// Right mouse pressed
				case SDL_BUTTON_RIGHT:
					//hide a widget if mouse is within its bound and it isn't already hidden
					if (CLOCK.insideBound(E.motion.x, E.motion.y) && !CLOCK.hidden)
						CLOCK.toggleHidden();
					if (StringQuote.insideBound(E.motion.x, E.motion.y) && !StringQuote.hidden)
						StringQuote.toggleHidden();
                    if (Date.insideBound(E.motion.x, E.motion.y) && !Date.hidden)
    					Date.toggleHidden();
					break;
				}
			break;
            // Mouse wheel scrolled
            case SDL_MOUSEWHEEL:
            // scale the unlocked, unhidden widgets
                if (!CLOCK.locked && !CLOCK.hidden)
                    CLOCK.changeFont("Comfortaa_Regular.ttf", CLOCK.getSize() + E.wheel.y);
                if (!StringQuote.locked && !StringQuote.hidden)
                    StringQuote.changeFont("Comfortaa_Regular.ttf", StringQuote.getSize() + E.wheel.y);
				if (!Date.locked && !Date.hidden)
					Date.changeFont("Comfortaa_Regular.ttf", Date.getSize() + E.wheel.y);
            break;

			case SDL_QUIT:
				end_main_loop = true;
				break;
			}
		}
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0);
	SDL_RenderClear(main_renderer);

	CLOCK.draw();
    StringQuote.draw();
	Date.draw();
	//update screen
	SDL_RenderPresent(main_renderer);
	}
    return 0;
}
