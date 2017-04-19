//
//  TextSnippet.h
//  Projec1
//
//  Created by Scott English on 4/8/17.
//  Copyright © 2017 Scott English. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "sqlite3.h"
#include "Widget.h"
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#ifndef TextSnippet_h
#define TextSnippet_h

class TextSnippet: public Widget
{
public:
    TextSnippet(int start_x, int start_y, SDL_Renderer *renderer, SDL_Window *window);
    void ChangeText();
    void draw();
    ~TextSnippet();
private:
    TTF_Font *font;
    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;
    int TimeElapsed;
    char *quote;

};

#endif /* TextSnippet_h */
