//
//  TextSnippet.cpp
//  Projec1
//
//  Created by Scott English on 4/8/17.
//  Copyright © 2017 Scott English. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include "TextSnippet.h"
#include "Widget.h"
#include "TextDatabase.cpp"
#include "TextDatabase.h"

TextSnippet::TextSnippet(int start_x, int start_y, SDL_Renderer *renderer, SDL_Window *window): Widget(start_x, start_y, renderer, window){
    // Load a font
    font = TTF_OpenFont("RAPSCALL.ttf", 24);
    if (font == NULL)
    {
        std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    SDL_Color text_color = {255, 255, 255};
    char *input="TextDataBase.db";
    textdatabase databaseinfo(input);
    quote=databaseinfo.Query();
    surfaceMessage = TTF_RenderText_Solid(font, quote, text_color);
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_QueryTexture(Message, NULL, NULL, &pos.w, &pos.h);
}
void TextSnippet::draw(){
    SDL_RenderCopy(renderer, Message, NULL, &pos);
}
void TextSnippet::ChangeText(){
    
}
TextSnippet::~TextSnippet()
{
    SDL_DestroyTexture(Message);
}

