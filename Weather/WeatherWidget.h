#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Widget.h"
using namespace std;

class Weather: public Widget {
public:
    Weather(int, int, SDL_Renderer*, SDL_Window, string);
    int getCurrentTemp();
    void updateWeather();
    void changeLocation(string); //TODO
    ~Weather();
private
    string currentTemp;
};
