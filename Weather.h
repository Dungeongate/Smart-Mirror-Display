#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include "Widget.h"
using namespace std;

class Weather {
public:
    Weather();
    string getCurrentTemp();
    void updateWeather();
    void changeLocation(string); //TODO
    ~Weather();
private:
    string currentTemp;
};
