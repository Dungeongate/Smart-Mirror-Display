#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sqlite3.h"
#include "Clock.h"
#include "Weather.h"
#include "Widget.h"
#include "Basic_Image.h"
#include "Text.h"
#include "TextDatabase.h"

int main(int, char**) {
    // Text Database Code //
    std::string QueryResult;
    const char *input="TextDataBase.db";
    textdatabase databaseinfo(input);


    databaseinfo.CountRows();
    QueryResult=databaseinfo.Query();

	//Initial clock code
	Clock c;
	std::string TIME;

    //Initialize Weather
    Weather w;

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
    SDL_Window *main_window = SDL_CreateWindow("GUI window test text", 100, 100, 1000, 900, SDL_WINDOW_SHOWN || SDL_WINDOW_RESIZABLE);
    if (main_window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 2;
    }
    int seconds_per_quote = 5;
    int seconds_per_weather = 15;
    int seconds_since_last_quote = 0;
    int seconds_since_last_weather = 0;
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

	Text CLOCK(300, 600, main_renderer, main_window, "RAPSCALL.ttf", text_color, c.getTime() , 50);
    Text StringQuote(200, 500, main_renderer, main_window, "RAPSCALL.ttf", text_color,QueryResult, 50);
    Text weather(200, 800, main_renderer, main_window, "RAPSCALL.ttf",text_color, w.getCurrentTemp(),50);
	bool end_main_loop = false;
    // Main Loop
    while (!end_main_loop){
	c.updateClock();
    	if (c.getTime() != last_second){
		SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0);
		SDL_RenderClear(main_renderer);
		CLOCK.draw();
        	StringQuote.draw();
        	weather.draw();

		//update screen
		SDL_RenderPresent(main_renderer);
		CLOCK.changeText(c.getTime());
        	last_second = c.getTime();
        	seconds_since_last_quote++;
		seconds_since_last_weather++;
    	}
    	if (seconds_since_last_quote >= seconds_per_quote){
       		// Get the new random quote into QueryResult
        	StringQuote.changeText(databaseinfo.Query());
        	seconds_since_last_quote = 0;
    	}
	if (seconds_since_last_weather >= seconds_per_weather){
		w.updateWeather();
		weather.changeText(w.getCurrentTemp());
		seconds_since_last_weather=0;
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
                weather.setX(weather.getX() - 15);
				break;
			// Right key pressed
				case SDLK_RIGHT:
				CLOCK.setX(CLOCK.getX() + 15);
				StringQuote.setX(StringQuote.getX() + 15);
                weather.setX(weather.getX() + 15);
				break;
			// Up key pressed
			case SDLK_UP:
				CLOCK.setY(CLOCK.getY() - 15);
				StringQuote.setY(StringQuote.getY() - 15);
                weather.setY(weather.getY() - 15);
				break;
			// Down key pressed
			case SDLK_DOWN:
				CLOCK.setY(CLOCK.getY() + 15);
				StringQuote.setY(StringQuote.getY() + 15);
                weather.setY(weather.getY() + 15);
				break;
			// show all hidden widgets
			case SDLK_SPACE:
                StringQuote.hidden = false;
                CLOCK.hidden = false;
                weather.hidden = false;
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
                    if (weather.insideBound(E.motion.x, E.motion.y))
                        weather.toggleLock();
					break;
				// Right mouse pressed
				case SDL_BUTTON_RIGHT:
					//hide a widget if mouse is within its bound and it isn't already hidden
					if (CLOCK.insideBound(E.motion.x, E.motion.y) && !CLOCK.hidden)
						CLOCK.toggleHidden();
					if (StringQuote.insideBound(E.motion.x, E.motion.y) && !StringQuote.hidden)
						StringQuote.toggleHidden();
                    if (weather.insideBound(E.motion.x, E.motion.y) && !weather.hidden)
                        weather.toggleHidden();
					break;
				}
			break;
            // Mouse wheel scrolled
            case SDL_MOUSEWHEEL:
            // scale the unlocked, unhidden widgets
                if (!CLOCK.locked && !CLOCK.hidden)
                    CLOCK.changeFont("RAPSCALL.ttf", CLOCK.getSize() + E.wheel.y);
                if (!StringQuote.locked && !StringQuote.hidden)
                    StringQuote.changeFont("RAPSCALL.ttf", StringQuote.getSize() + E.wheel.y);
                if (!weather.locked && !weather.hidden)
                    weather.changeFont("RAPSCALL.ttf", weather.getSize() + E.wheel.y);
            break;

	    case SDL_QUIT:
		end_main_loop = true;
		break;
            }
	}
	SDL_Delay(1);
    }
    return 0;
}
